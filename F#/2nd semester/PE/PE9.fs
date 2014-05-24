(*
    This program is made by Bolotov Sergey (Болотов Сергей).
    Year 2013, SPSU, MM faculty, gr. 171.
    Problem 9: There exists exactly one Pythagorean triplet for which a + b + c = 1000.
	Find the product abc.
*)
module PE9
open System

for a in 1..1000 do
    for b in 1..1000-a do
        let c = 1000-a-b
        if b*b+a*a = c*c then printfn "%A" <| a*b*c
