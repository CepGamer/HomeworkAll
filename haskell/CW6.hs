{-
    Classwork 6, Bolotov Sergey
-}
{-
data T a b = N {h :: Integer, key :: a, values :: [b], left :: (T a b), right :: (T a b)} | L deriving Show
-}

{-
    Типовые выражения: 
        Boolean, Integer; 
        a, b;
        t1 -> t2: t1, t2 - тип. выр.
        (t1, t2, .., tk): t_i - тип. выр.
        t1 t2: t1, t2 - тип. выр.

    Parser a = String -> a - именно '='' !
    data нельзя,  type можно:
    type Parser a = String -> a
    data - алгебраический тип, type - любой.    //  google: "алгебраический тип"

    Например:
    type Vector = ([Integer], Integer)
    
    Собственно, задача:
    type Parser a = String -> a
    Вообще даже так:
    type Parser a = String -> [(a, String)], причём: а - расп. часть, String - хвост.


    John Huges

    Написать: 
    sym :: Char -> Parser Char
    val :: a -> Parser a
    (|||) :: Parser a -> Parser a -> Parser a
    (||>) :: Parser a -> (a -> Parser b) -> Parser b
    (*(sym 'a' ||> (\a -> sym 'b' ||> (\b -> val (a, b)))) "abc" = [(('a', 'b'), "c")]*)
    many: :: Parser a -> Parser [a]
    opt :: Parser a -> Parser (Maybe a)

    Написать: синтаксический анализатор C. (выражений С: +,-,*,/,%,>>>,<<<,||,&&,++,--. И скобки)
    Подсказка: мы всё это уже умеем.
    Беречься левой рекурсии.
-}

type Parser a = String -> [(a, String)]

sym :: Char -> Parser Char
sym a (x:xs)
    | x == a = [(a, xs)]
sym a _ = []

val :: a -> Parser a
val a s = [(a, s)]

infixl 2 |||
(|||) :: Parser a -> Parser a -> Parser a
a (|||) b = \s -> a s ++ b s

infixl 3 ||>
(||>) :: Parser a -> (a -> Parser b) -> Parser b
p (||>) q = \s -> concat [q a s | (a, s) <- p s]

many :: Parser a -> Parser [a]
many a = a ||> (\x -> many a ||> val . (x:)) ||| val []

{-
//a* = aa* | empty
many a = a (many a) | empty
    = a ||> (\x -> many a) | empty
        = a ||> (\x -> many a ||> (\xs -> val (x:xs))) ||| val []
-}

opt :: Parser a -> Parser (Maybe a)
opt a = a ||> val . Just || val Nothing 
