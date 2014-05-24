(*
    This program is made by Bolotov Sergey (Болотов Сергей).
    Year 2013, SPSU, MM faculty, gr. 171.
    Problem 1: Find the sum of all the multiples of 3 or 5 below 1000.
*)
module PE1
open System
let a = List.filter (fun x -> (x % 5 = 0) || (x % 3 = 0) ) [1..1000 - 1]
printfn "%A" <| List.sum a
