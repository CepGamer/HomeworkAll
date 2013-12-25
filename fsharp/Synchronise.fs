open System

let curr = ref 0
let quan = 5
let rand = new Random()
let arrOfRand = [|for i in 1..quan -> rand.Next(10000)|]

let printProc num = 
    lock curr (fun () ->
        if !curr = num - 1 then
            printfn "Process # %A finished its business" <| num
            curr := !curr + 1
            false
        else true
        )

let proces num = 
    async {
        do! Async.Sleep arrOfRand.[num - 1]
        while (printProc num) do
            do! Async.Sleep 100
    }

[<EntryPoint>]
let main argc = 
    let arr = [|for i in 1..quan -> proces i|]
    arr |> Async.Parallel |> Async.RunSynchronously |> ignore
    0
