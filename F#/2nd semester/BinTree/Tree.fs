(*
    This program is made by Bolotov Sergey (Болотов Сергей).
    Year 2013, SPSU, MM faculty, gr. 171.
*)
module Tree
open System

let WIDTH = 10
type BinTree<'a> =  //  recurrent definition of Binary Tree
    | None  //  Leaf
    | Bud of 'a * BinTree<'a> * BinTree<'a> //  Bud contains: value, left branch and right branch

let rec add tree value = 
    match tree with
    | Bud (a, left, right) -> if value > a then add right value else add left value //  Here we go left or right down the tree
    | None -> Bud (value, None, None)   //  And here we stop & add

let rec find tree value = 
    match tree with
    | None -> false //  Because no
    | Bud (a, _, _) when a = value -> true  //  If equals - then it exists
    | Bud (a, left, right) -> find left value || find right value   //  Else - continue searching for it

let rec delete tree value =  //  Here goes the problem...
    match tree with
    | None -> None  //  We kinda not changin' it - because don't need to
    | Bud (a, None, None) when a = value -> None    //  When Bud is a leaf - we simply delete it
    | Bud (a, None, r) when a = value -> r          //  Replace with branch
    | Bud (a, l, None) when a = value -> l          //  Similar
    | Bud (a, l, r) when a = value ->               //  Delete bigger elem from tha tree (tha righter)
        let a = 
            let rec retMax x =  //  Return value of the "righest" element
                match x with
                | Bud ( a, _, None ) -> a       //  Simple
                | Bud ( a, _, r ) -> retMax r   //  Go further
            retMax l                //  Delete biggest value
        Bud ( a, delete l a, r )             //  Return Bud with biggest element on top of it
    | Bud (a, l, r) -> if value > a then delete r value else delete l value //  If not equals to value - go further and look for it

let binTreeDepth tree =     //  Check for tree depth (Sincerely Yours, Captain)
    let rec dep tre acc = 
        match tre with
        | None -> acc
        | Bud (_, l, r) -> max (dep l acc + 1 ) ( dep r acc + 1 )
    dep tree 0

let draw tree =     //  Prints the tree
    let rec drawSpaces boolList =   //  Prints spaces before tree
        match boolList with
        | true::t -> 
            printf "|%s" <| (String.replicate (WIDTH - 1) "-").Trim ('\"')
            drawSpaces t
        | false::t -> 
            printf "%s" <| (String.replicate WIDTH " ").Trim ('\"')
            drawSpaces t
        | _ -> ignore 5
    let rec drawElem tre lev boolList =     //  My drawing
        match tre with
        | None ->
            printfn "Nya"   //  Because it's the end of the branch
        | Bud (a, l, r) ->  //  Here we go with printing
            printf "%d%s" a ( (String.replicate (WIDTH - a.ToString().Length) "-").Trim ('\"') )  //  Cause we need to print element
            drawElem l ( lev + 1 ) (true::boolList)         //  Then we print smaller branch
            drawSpaces boolList
            drawElem r ( lev + 1 ) (false::boolList)        //  And, at last, we drawing larger element
            printfn ""
    let rec drawElemWiki tre lev =          //  Wiki drawing
        match tre with
        | None -> 
            for i in 1..lev do printf "\t"
            printfn "Nyathing is Nyear"
        | Bud (a, None, None) -> 
            for i in 1..lev do printf "\t"
            printfn "(%d Nyan Nyan)" <| a
        | Bud (a, l, r) -> 
            for i in 1..lev do printf "\t"
            printfn "(%d" <| a
            drawElemWiki l (lev + 1)
            drawElemWiki r (lev + 1)
            for i in 1..lev do printf "\t"
            printfn ")"

    drawElemWiki tree 0 //  Starting point

let a = Bud(5, Bud(3, Bud(2, Bud(1, None, None), None), Bud(4, None, None)), Bud(75, Bud(6, None, None), Bud(815, None, None)))
draw a
