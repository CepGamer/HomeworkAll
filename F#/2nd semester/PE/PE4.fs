(*
    This program is made by Bolotov Sergey (Болотов Сергей).
    Year 2013, SPSU, MM faculty, gr. 171.
    Problem 4: Find the largest palindrome made from the product of two 3-digit numbers.
*)
module PE4
open System
let palin n = 
    let mutable f = true
    for i in 0..( String.length <| n ) / 2 + 1 do 
        if n.[i] <> n.[ String.length (n) - i - 1 ] then f <- false
    f

let mutable a = 0
for i in 100..999 do
    for j in 100..999 do
        if palin <| ( i*j ).ToString() then a <- Math.Max (a, i*j)

printfn "%A" <| a

ignore <| Console.ReadKey()