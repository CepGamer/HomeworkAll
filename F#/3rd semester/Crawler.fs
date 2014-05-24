module WebCrawler

open System
open System.Text.RegularExpressions
open System.Net
open System.IO
open System.Collections.Concurrent
open System.Collections.Generic
open System.Threading
open System.Xml
open HtmlAgilityPack

type List<'T> with
    static member normalise xs = 
        List.fold (fun acc x -> if List.tryFind ((=) x) acc <> None then acc else x::acc) [] xs

let startUrl = "http://www.gameland.ru/"

let minImgSize = 1024               //  kb
let maxImgSize = 3 * 1024 * 1024    //  3 Mb

let client = new WebClient()


let regImg = new Regex("http:\/\/[\w\/\.]*\.(ico|gif|png|svg|jpe?g)")
let regEnd = new Regex("\.(ru|com|net)[\w\/\.]*")

let isSubUrl domain (sub: string) = sub.StartsWith domain

let folder = sprintf "%s\\%s" (Environment.GetFolderPath Environment.SpecialFolder.MyPictures) (regEnd.Replace (startUrl.TrimStart("http://".ToCharArray()), ""))

let downloaded = new ConcurrentDictionary<string, bool>()
let visited = new ConcurrentDictionary<string, bool>()

let trimPath (path: string) = 
    let a = path.LastIndexOf('/')
    path.Substring(a, path.Length - a)

let toDom (url:string) = 
    if url.StartsWith "http://" then
        url
    else
    if url.StartsWith "/" then
        sprintf "%s%s" startUrl <| url.TrimStart '/'
    else
        url

let downloadImgAsync (path: string) = async {
    try
        if not <| downloaded.ContainsKey path then
            let q = WebRequest.Create path
            let r = q.GetResponse()
            let size = int r.ContentLength
            r.Close()
            if size >= minImgSize && size <= maxImgSize then
                (new WebClient()).DownloadFileAsync(Uri(path), sprintf "%s\\%s" folder (trimPath path))
                downloaded.GetOrAdd (path, true) |> ignore
    with
        | ex -> ()
}

let findPics (html: HtmlDocument) = async {
    try
        let urls = List.ofSeq (new List<HtmlNode>(html.DocumentNode.Descendants("img")))
                   |> List.map (fun (x:HtmlNode) -> x.Attributes.["src"].Value) 
                   |> List.map toDom
                   |> List.filter (fun x -> regImg.IsMatch x && not <| downloaded.ContainsKey x)
        return urls
    with | ex -> return []
}

let findUrls dom (html: HtmlDocument) = async {
    try
        let urls = List.ofSeq (new List<HtmlNode>(html.DocumentNode.SelectNodes("//a[@href]")))
                   |> List.map (fun (x:HtmlNode) -> x.Attributes.["href"].Value)
                   |> List.map toDom
                   |> List.filter (fun x -> isSubUrl dom x && not <| visited.ContainsKey x)
        return urls
    with | ex -> return []
}

let rec downloadUrl (url: string) = async {
    try
        let doc = new HtmlDocument ()
        let! html = client.AsyncDownloadString <| Uri url
        doc.LoadHtml html
        visited.GetOrAdd (url, true) |> ignore
        let! urls = findUrls url doc
        let! pics = findPics doc
        let newAsyncPics = [for i in pics -> downloadImgAsync i]
        let newAsyncUrls = [for i in urls -> downloadUrl i]
        newAsyncPics |> Async.Parallel |> Async.RunSynchronously |> ignore
        newAsyncUrls |> Async.Parallel |> Async.RunSynchronously |> ignore
    with | ex -> ()
}
    

[<EntryPoint>]
let main argc = 
    if not <| Directory.Exists folder then Directory.CreateDirectory folder |> ignore
    downloadUrl startUrl |> Async.RunSynchronously
    0
