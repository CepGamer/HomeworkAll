(*
    This program is made by Bolotov Sergey (Болотов Сергей).
    Year 2013, SPSU, MM faculty, gr. 171.
    Problem 2: By considering the terms in the Fibonacci sequence whose values do not exceed four million, find the sum of the even-valued terms.
*)
module PE2
open System
let f = 
    let rec crL a = 
        match a with
        | h::t when h < 4000000L -> crL ( (h + t.Head)::a)
        | _ -> a
    crL [1L;1L]
printfn "%A" <| List.sum (List.filter (fun x -> x % 2L = 0L) f)

