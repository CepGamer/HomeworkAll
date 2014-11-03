{-
    Homework #7: Parser
    Made by: Bolotov Sergey
    +, -, *, /, %, &&, ||, >, >=, <, <=, !=, ==
    funcs, vars, ()
    hometask1: multi = primary | primary op multi = primary (op primary)* through foldl
    HT2: reuse of structures multi, logi etc.
    ЧИТАТЬ КОМБИНАТОРЫ БЛЕАТЬ
-}

type Parser a = String -> [(a, String)]

empty :: Parser a
empty _ = []

infixl 2 |||
(|||) :: Parser a -> Parser a -> Parser a
a ||| b = \s -> a s ++ b s

infixl 3 ||>
(||>) :: Parser a -> (a -> Parser b) -> Parser b
p ||> q = \s -> concat [q a s | (a, s) <- p s]

sym :: Char -> Parser Char
sym a (x:xs)
    | x == a = [(a, xs)]
sym a _ = []

val :: a -> Parser a
val a s = [(a, s)]

many :: Parser a -> Parser [a]
many a = a ||> (\x -> many a ||> val . (x:)) ||| val []

{-opt :: Parser a -> Parser (Maybe a)
opt a = a ||> val . Just || val Nothing
-}
data E = X String | N Integer | Mul E E | Div E E | 
    Add E E | Sub E E | 
    GrT E E | LeT E E | 
    LeE E E | GrE E E | 
    Eq E E | NE E E |
    As E E deriving Show -- Тип данных для синтаксической единицы

oneOf :: [Char] -> Parser Char
oneOf = foldl (\a b -> a ||| sym b) empty

letter :: Parser Char
letter = oneOf (['_'] ++ ['a'..'z'] ++ ['A'..'Z'])
digit = oneOf ['0'..'9']

ident = letter ||> (\x -> many (letter ||| digit) ||> (\xs -> val $ X (x:xs)))

literal = digit ||> (\x -> many digit ||> (\xs -> val $ N $ read (x:xs)))

primary = 
    ident ||| literal |||
    sym '(' ||> (\ _ -> expr ||> (\e -> sym ')' ||> (\ _ -> val e)))

next c a p b = p (c a) b --Список дырка парсер далее -> парсер (список дырка) далее

{-
multi = primary | primary op multi = primary (op primary)*
-}
multi c = 
    primary |||
    --primary ||> (\ a -> sym '*' ||> (\ as -> multi))
    --было:    primary ||> (\x -> op ||> (\o -> multi ():xs ||> (\y -> val $ (xs x) `o` y)))
    --Стало:
    primary ||> (\x -> op ||> (\o -> multi $ next c x o))
    where op = sym '*' ||> (\_ -> val Mul) ||| sym '/' ||> (\_ -> val Div)

addi = 
    multi |||
    multi ||> (\x -> op ||> (\o -> addi $ next c x o))
    where op = sym '+' ||> (\_ -> val Add) ||| sym '-' ||> (\_ -> val Sub)

{-
rely = ident '=' expr | expr ('>'|'<'|">="|"<="|"=="|"!=") expr
-}

rely = 
    addi ||> (\x -> op ||> (\o -> addi ||> (\y -> val $ x `o` y))) 
--    ident ||> (\x -> (sym '=' ||> (\_ -> val As)) ||> expr (\y -> As x y)) ||| 
  --  addi ||> (\x -> op ||> (\o -> expr ||> (\y -> val $ o x y)))
    where op = sym '>' ||> (\_ -> val GrT) ||| sym '<' ||> (\_ -> val LeT)

{-
logi = 
-}

expr = addi
