(*
    This program is made by Bolotov Sergey (Болотов Сергей).
    Year 2013, SPSU, MM faculty, gr. 171.
    Problem 72: Find how many elements would be contained in the set of reduced proper fractions for d <= 1,000,000.
*)

module PE72
open System

let MAGIC = 1000001

let rec gcd n m = 
    if n = m then n
    else if n = 1 || m = 1 then 1
    else if n = 0 then m
    else if m = 0 then n
    else if n > m then gcd m ( n % m )
    else gcd n ( m % n )

let minMult n = 
    let mutable i = 2
    let mutable loop = true
    while i * i <= n && loop do
        if n % i = 0 then loop <- false
        i <- i + 1
    if loop then 1 else i - 1

let phi = 
    let a: int array = Array.zeroCreate MAGIC
    a.[0] <- 0
    a.[1] <- 1
    a.[2] <- 1
    let insPhi n = 
        let f = minMult n
        let z = gcd f ( n / f )
        if f = 1 then n - 1 else a.[f] * a.[n / f] * z / a.[z]
    for i in 3..MAGIC - 1 do
        if i % 1000000 = 0 then printfn "NewLine"
        a.[i] <- insPhi i
    a

let permutation n = 
    let mutable a = Array.zeroCreate 10
    let mutable b = Array.zeroCreate 10
    let mutable x = n
    while x > 0 do
        a.[x % 10] <- a.[x % 10] + 1
        x <- x / 10
    x <- phi.[n]
    while x > 0 do
        b.[x % 10] <- b.[x % 10] + 1
        x <- x / 10
    let mutable l = true
    for i in 0..9 do
        if a.[i] <> b.[i] then l <- false
    l

let mutable n = 0L
for i in 2..MAGIC - 1 do
    n <- n + int64 phi.[i]
    //printfn "%A" <| n

printfn "%A" <| n
