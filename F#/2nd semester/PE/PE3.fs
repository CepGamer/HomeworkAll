(*
    This program is made by Bolotov Sergey (Болотов Сергей).
    Year 2013, SPSU, MM faculty, gr. 171.
    Problem 3: Find the largest prime factor of the number 600851475143.
*)
module PE3
open System
let a = 600851475143L
let rec bigPrimeDiv a i = 
  if a = 1L then (i - 1L)
  else bigPrimeDiv (if a % i = 0L then a / i else a) (i + 1L)
printfn "%A" <| bigPrimeDiv a 2L 

