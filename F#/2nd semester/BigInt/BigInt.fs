(*
    This program is made by Bolotov Sergey (Болотов Сергей).
    Year 2013, SPSU, MM faculty, gr. 171.
*)
module BigInt
open System

let powOf10 pow =   //  Return 10^pow
    let mutable a = 1
    for i in 1..pow do a <- a * 10
    a

let logOf10 num = 
    let rec ins n acc = 
        if n / 10 > 0 then ins (n / 10) (acc + 1)
        else acc
    ins num 0 + 1

type bigNumber (init:string) =  //   Represents class for long arithm
    let ONE_INT_LENGTH = 9
    let MILLIARD = 1000000000
    let ValueString = if init.StartsWith "-" then init.Substring <| 1 else init //  String that represents number without sign. Why do I need it?
    member x.Sign = if init.StartsWith <| "-" then true else false  //  Bool member for sign of the number
    member x.Length = init.Length - (if x.Sign then 1 else 0)       //  Length of the number (maybe I'll need it sometime. Maybe)
    member x.Value =    //  Value of BigInt represented as list. We pretend that input has no errors (like char's and other stuff) in it
        let mutable f = []
        let rec parseSt lst i =     //  Parse string into list
            match lst with  //  Well, I'm not gonna comment this long line of code. Only 'It's magic!'
            | [] -> [ Int32.Parse ( ValueString.Substring( i * ONE_INT_LENGTH, Math.Min( ONE_INT_LENGTH, ValueString.Length - i * ONE_INT_LENGTH) ) ) * powOf10 ( 9 - Math.Min( ONE_INT_LENGTH, ValueString.Length - i * ONE_INT_LENGTH ) ) ]
            | h::t -> h :: parseSt t i  //  We just add new number to an end
        for i in 0..ValueString.Length / ONE_INT_LENGTH + (if ValueString.Length % ONE_INT_LENGTH > 0 then 0 else -1) do
            f <- parseSt f i
        f

    member this.getByNumber x = //  Fun that returns number from position. Starts with 1
        let rec gbn a x = 
            match a with
            | [] -> -1  //  If we're out of range (everything could happen)
            | h::t -> 
                if x > ONE_INT_LENGTH then gbn t (x - ONE_INT_LENGTH)   //  Take one step further
                else (h / powOf10(ONE_INT_LENGTH - x) ) % 10            //  Cut the left part, then - the right part.
        if this.Length < x then -1  //  Because go to hell, please
        else gbn (this.Value) x     //  Else - you're a good boy

    interface IComparable<bigNumber> with   //  Implement IComp, I hope this one works well
        member this.CompareTo obj = 
            if this.Sign && not obj.Sign then -1         //  -abs(x) < abs(x) all the time
            else if obj.Sign && not this.Sign then 1   //  Absolutely negative part
            else if obj.Length <> this.Length then (if this.Sign then -1 else 1) * (if this.Length > obj.Length then 1 else -1)
            else    //  Line up there check for length and sign: returns sign(this) * (this.Length > obj.Length)
                let rec cmpr a (b:list<int>) = 
                    match a with
                    | [] -> 0   //  End of the line
                    | h::t ->
                        if h > b.Head then 1        //  'Cause bigger
                        else if h < b.Head then -1  //  'Cause smaller
                        else cmpr t b.Tail          //  This is not the end
                cmpr this.Value obj.Value   //  This is

    //interface IFormattable with             //  Returns string that equal to our number
    override this.ToString() = 
        (if this.Sign then "-" else "") + ((List.foldBack (fun h acc -> ((String.replicate(ONE_INT_LENGTH - logOf10 h) "0") + h.ToString()) + acc) this.Value "").Substring( 0, this.Length))

    static member (+) (x:bigNumber, y:bigNumber) = 
        let ONE_INT_LENGTH = 9
        let moveRight (a:bigNumber) c =                 //  Move right some digits
            let rec moveRight x c acc =     // Move right some digits less than ONE_INT_LENGTH
                match x with
                | [] when acc = -1 -> [0]   //  If we're outta range - must take into account that that list must be 'normalized'
                | [] when acc = 0 -> []     //  Else - we don't give a... thing. Kinda strange choice of numbers, huh?
                | [] -> [acc]               //  Else - Nike (Just Do It. That's what I meant. Not go and sell shoes because of unsuitability for the occupation of programmer)
                | h::[] ->
                    let shift = if ONE_INT_LENGTH - (a.Length % ONE_INT_LENGTH) < c then -1 else (h % (powOf10 c)) //  shift accumulator
                    (acc * (powOf10 (ONE_INT_LENGTH - c)) + h / (powOf10 c))::(moveRight [] c shift)  

                | h::t ->
                    (acc * (powOf10 (ONE_INT_LENGTH - c)) + h / (powOf10 c))::(moveRight t c (h % (powOf10 c)))
            let mutable h = a.Value
            for i in 1..(c + (a.Length % ONE_INT_LENGTH)) / ONE_INT_LENGTH do
                h <- 0::h
            moveRight h (ONE_INT_LENGTH - (a.Length % ONE_INT_LENGTH)) 0
        let mutable h = moveRight x (max x.Length y.Length - x.Length + 1)
        let mutable t = moveRight y (max x.Length y.Length - y.Length + 1)
        let sumLists a b =          //  Here we know that a.Length equals to b.Length
            let a' = List.rev a         //  Reverse - it's easier to work with them when they are reversed
            let b' = List.rev b 
            let rec sl a (b:list<int>) acc =    //  Because when reversed, we can pass forward the acc - the "Big" part which needs to be cut off
                match a with
                | [] -> []          //  End of operation
                | h::t when b = [] ->           //  We add, cut off part that bigger than 1 milliard and continue
                    ((h + acc) % powOf10 ONE_INT_LENGTH)::[]
                | h::t ->           //  We add, cut off part that bigger than 1 milliard and continue
                    ((h + b.Head + acc) % powOf10 ONE_INT_LENGTH)::(sl t b.Tail ((h + b.Head + acc) / powOf10 ONE_INT_LENGTH))
            printfn "%A" <| a
            let f = sl a' b' 0
            List.rev <| sl a' b' 0
        let subLists a b =              //   Here we MUST provide that a is bigger than b. And they are length-equal
            let a' = List.rev a         //  Reverse - again, it's easier to work with them when they are reversed
            let b' = List.rev b 
            let rec sl a (b:list<int>) acc = 
                match a with
                | [] -> []          //  End of the line, step off the board
                | h::t ->           //  Subtract, don't cut off anything (except sign) and pass forw dat sign
                    let arr = h - b.Head + acc
                    (if arr > 0 then arr else (powOf10 ONE_INT_LENGTH + arr))::(sl t b.Tail (Math.Sign((Math.Sign (h - b.Head)) - 1)))
            List.rev <| sl a' b' 0
        let f = h > t
        let z =                     //  List with dem result
            match x.Sign with
            | true when y.Sign -> sumLists h t      //  Signs are equal - sum up
            | false when not y.Sign -> sumLists h t //  Again
            | _ ->
                if f then subLists h t              //  Signs differ - we need to subtract from bigger one
                else subLists t h
        let arr = (List.foldBack (fun h acc -> (String.replicate(ONE_INT_LENGTH - logOf10 h) "0") + h.ToString() + acc) z "").TrimStart("0".ToCharArray())
        let arrr = arr.Substring(0, min (max x.Length y.Length + 1) arr.Length )
        bigNumber((if (f && x.Sign) || (x.Sign && y.Sign) then "-" else "") + arrr)
    static member (-) (x:bigNumber, y:bigNumber) =  //  Just change sign of y and -> (+)
        let a = y.ToString()
        let f = a.StartsWith "-"
        x + bigNumber((if f then "" else "-") + a.TrimStart ("-".ToCharArray()))
    member private this.mulBy10() =       //  Add '0' to the end of the number
        bigNumber(this.ToString() + "0")
    member private this.divBy10() =       //  Take last dec the end of the number
        bigNumber(this.ToString().Substring(0, this.Length - (if this.Sign then 0 else 1)))
    static member (*) (x:bigNumber, y:bigNumber) =  //  Multiplying through (+)
        let mutable f = bigNumber("0")
        let mutable z = bigNumber(x.ToString().TrimStart("-".ToCharArray()))
        for i in 1..y.Length do
            for j in 1..y.getByNumber (y.Length - i + 1) do
                f <- f + z
            z <- z.mulBy10()
        bigNumber((if ((x.Sign || y.Sign) && not (x.Sign && y.Sign)) then "-" else "") + f.ToString())

let a = bigNumber ("123456789123")
let b = bigNumber ("900000000000")
let z = a * b
printfn "%A" <| z.ToString()

