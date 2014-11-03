(*
    This program is made by Bolotov Sergey (Болотов Сергей).
    Year 2013, SPSU, MM faculty, gr. 171.
    Problem 7: Find the 10 001st prime number.
*)
module PE7
let isPrime n = 
    let mutable i = 2L
    while i * i < n do
        if n % i = 0L then i <- n
        else i <- i + 1L
    i * i > n && i <> n
let a = Array.filter isPrime [|2L..1000000L / 2L|]
printfn "%A" a.[10001 - 2]
