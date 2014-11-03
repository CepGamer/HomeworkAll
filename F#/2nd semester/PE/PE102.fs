(*
    This program is made by Bolotov Sergey (Болотов Сергей).
    Year 2013, SPSU, MM faculty, gr. 171.
    Problem 102: Using triangles.txt, a text file containing the co-ordinates of one thousand "random" triangles, 
    find the number of triangles for which the interior contains the origin.
*)
module PE102
open System

let mutable count = 0
let input = new IO.StreamReader ( "triangles.txt" )
while not input.EndOfStream do
    let mutable a = 0
    let mutable x: float array = Array.zeroCreate 3
    let mutable y: float array = Array.zeroCreate 3
    let f = ( input.ReadLine() ).Split <| ",".ToCharArray ()
    for j in 0..2 do
        x.[j] <- Double.Parse <| f.[ j * 2 ]
        y.[j] <- Double.Parse <| f.[ j * 2 + 1 ]
    let mutable t = ( y.[0] - x.[0] ) / ( x.[1] - x.[0] + y.[0] - y.[1] )
    let mutable s = t * ( x.[1] - x.[0] ) + x.[0]
    if s > 0.0 && t > 0.0 && t <= 1.0 then a <- a + 1
    t <- ( y.[0] - x.[0] ) / ( x.[2] - x.[0] + y.[0] - y.[2] )
    s <- t * ( x.[2] - x.[0] ) + x.[0]
    if s > 0.0 && t > 0.0 && t <= 1.0 then a <- a + 1
    t <- ( y.[1] - x.[1] ) / ( x.[2] - x.[1] + y.[1] - y.[2] )
    s <- t * ( x.[2] - x.[1] ) + x.[1]
    if s > 0.0 && t > 0.0 && t <= 1.0 then a <- a + 1
    if a = 1 then count <- count + 1
printfn "%A" <| count
