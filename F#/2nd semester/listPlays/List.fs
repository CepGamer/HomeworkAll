(*
    This program is made by Bolotov Sergey (Болотов Сергей).
    Year 2013, SPSU, MM faculty, gr. 171.
*)
//module List
open System
let rec addToEnd a x = 
    match a with
    | h :: t -> h :: addToEnd t x
    | [] -> [x]

let rec append a b = 
    match a with
    | [] -> b
    | h :: t -> h :: append t b

let rec reverse a = 
    let rec rev l acc = 
        match l with
        | h :: t -> rev t ( h :: acc )
        | [] -> acc
    rev a []

let rec find foo a = 
    match a with 
    | h :: t -> if foo h then Some h else find foo t
    | [] -> None

let map foo a = List.foldBack ( fun h acc -> (foo h) :: acc ) a []

let check = 
    printfn "%A" <| if addToEnd [1;2] 3 = [1..3] then "Hooray! addToEnd works!" else "Error in addToEnd"
    printfn "%A" <| if append [1;2] [3;4] = [1..4] then "Hooray! append works!" else "Error in append"
    printfn "%A" <| if reverse [1..4] = [4..-1..1] then "Hooray! reverse works!" else "Error in reverse"
    printfn "%A" <| if find ( (<) 4 ) [1..5] = Some 5 then "Hooray! find works!" else "Error in find"
    printfn "%A" <| if map (fun x->x+2) [1..4] = [3..6] then "Hooray! map works!" else "Error in map"
check
