(*
    This program is made by Bolotov Sergey (Болотов Сергей).
    Year 2013, SPSU, MM faculty, gr. 171.
    Problem 5: Find the smallest positive number that is evenly divisible by all of the numbers from 1 to 20.
*)
module PE5
open System

let isPrime x = 
    let rec isPrimeTemp x i = 
        if i * i > x then true 
        else if x % i = 0 then false
        else isPrimeTemp x ( i + 1 )
    isPrimeTemp x 2

let a = ref 1
for i in 2..20 do
    if isPrime i then a := !a * ( int <| Math.Pow ( float i, float ( int <| Math.Log ( float 20, float i ) ) ) )

printfn "Answer is: %A" !a
