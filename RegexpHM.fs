open System.Text.RegularExpressions

let localPart = "[0-9a-zA-Z\-_\+]+(\.[0-9a-zA-Z\-_\+]+)*"
let domainPart = "([0-9a-zA-Z\-_]+\.)+"
let sitePart = "([a-zA-Z]{2, 4}|yandex|museum|domain)"

let pattern = "^" + localPart + "@" + domainPart + sitePart + "$"

let test = 
    let a = new Regex ( pattern )
    let arr = [|"niceandsimple@example.com";
             "a.little.lengthy.but.fine@dept.example.com";
             "disposable.style.email.with+symbol@example.com";
             "Abc.example.com";
             "A@b@c@example.com"|]
    for i in 0..4 do 
        if i < 3 then printfn "%A" <| a.IsMatch ( arr.[i] )
        else printfn "%A" ( a.IsMatch (arr.[i]) = false )

test
