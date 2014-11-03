(*
    This program is made by Bolotov Sergey (Болотов Сергей).
    Year 2013, SPSU, MM faculty, gr. 171.
    Problem 6: Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.
*)
module PE6
open System
printfn "%A" <| (fun x -> x * x) (List.sum [1..100]) - List.sum (List.map (fun x -> x * x) [1..100])
