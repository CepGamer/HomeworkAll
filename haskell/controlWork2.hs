--Первое задание
fromFun _ [] = []
fromFun fun (a:as) = [(a, fun a)] ++ fromFun fun as

--fromFun f x = zip x (map f x)

--Второе задание
dom (a:as) = [fst a] ++ dom as

--Третье задание
eval [] _ = error "Value is not defined"
eval (a:as) f = if fst a == f then snd a else eval as f

--Четвёртое задание
invert (a:as) = [(snd a, fst a)] ++ invert as

--Пятое задание
infixl 9 .*.
x .*. y = [(fst a, snd b) | a <- y, b <- x, snd a == fst b]

--Верный вариант
-- x .*. y = [(a, d) | (a, b) <- y, (c, d) <- x, b == c]
--И вообще - все fst и snd заменить на (a, b)


--Шестое задание (normalize - сделан уже для правильности)
image x y = normalize [snd a | b <-y, a <- x, fst a == b]

--Седьмое задание
preimage x y = normalize [fst a | b <- y, a <- x, snd a == b]

--Восьмое задание
normalize [] = []
normalize (x:xs) = x : normalize [z | z <- xs, z /= x]
isInjective x = length [snd a | a <- x ] == length (normalize [snd a | a <- x])

--Девятое задание
isSurjective x = length x == -1

--Десятое задание
areMutuallyInverse x y = a == length x && a == length y && b == 0 where
    z = (x .*. y)
    a = length z
    b = length (filter (\x -> fst x /= snd x) z)

