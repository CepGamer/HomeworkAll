module eRegExp
open System.Text.RegularExpressions
open FsUnit
open NUnit.Framework

let isEmail candidate = 
    let letter = "a-zA-Z"
    let digit = "0-9"
    let other = "!#$%^&*()_\-\+/"
    let all = letter + digit + other

    let first = "^[_" + letter + "]"
    let name = "([.]?[" + all + "]){0, 30}"
    let left = first + name
    let sitename = "(aero|asia|coop|jobs|mobi|museum|post|travel|[" + letter + "]{2, 3})"
    let right = "([" + all + "]{1, 30}\.)+" + sitename + "$"
    let checker = new Regex(left + "@" + right)
    checker.IsMatch candidate

[<TestFixture>]
type emailTests() = 
    let corr = ["a@b.cc"
                "victor.polozov@mail.ru"
                "my@domain.info"
                "_.1@mail.com"
                "coins_department@hermitage.museum"]

    let incorr = [  "a@b.c"
                    "a..b@mail.ru"
                    ".a@mail.ru"
                    "yo@domain.somedomain"
                    "1@mail.ru" ]
    
    [<Test>]
    member x.good() = 
        List.iter (fun f -> isEmail f |> should be True) corr 

    [<Test>]
    member x.bad() = 
        List.iter (fun f -> isEmail f |> should be False) incorr
