(*
    This program is made by Bolotov Sergey (Болотов Сергей).
    Year 2013, SPSU, MM faculty, gr. 171.
    Problem 10: Find the sum of all the primes below two million.
*)
module PENot10
open System
let isPrime n = 
    let mutable i = 2L
    let mutable loop = true
    while ( i * i <= n ) && loop do
        loop <- if n % i = 0L then false else true
        i <- i + 1L
    loop

let mutable a = 2L
for i in 3L..2000000L do
    if isPrime i then a <- a + i

printfn "%A" <| a
