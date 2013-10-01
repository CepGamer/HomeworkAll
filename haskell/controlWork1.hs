-- Первое задание
zipWith' _ _ [] = []
zipWith' _ [] _ = []
zipWith' f (a:as) (b:bs) = (f a b) : zipWith' f as bs

-- Первое задание, лучший вариант
zipWith' f (a:as) (b:bs) = (f a b) : zipWith' f as bs
zipWith' _ _ _ = []

-- Второе задание
sprod x y = foldl (+) 0 (zipWith' (*) x y)

-- Третье задание
xIn _ [] = False
xIn x (a:as) = (x == a) || xIn x as
normalize [] = []
normalize (a:as) = if not (xIn a as) then (a : normalize as) else normalize as

-- Лучше так:
-- normalize (x:xs) = x : normalize [z | z <- xs, z /= x]

-- Четвёртое задание
sort [] = []
sort [a] = [a]
sort (a:as) = sort (filter (< a) as) ++ [a] ++ sort (filter (>= a) as)

-- Можно убрать sort [a]

-- Пятое задание
isProgression [] = True
isProgression [_] = True
isProgression [_, _] = True
isProgression (a:b:c:cs) = (b - a == c - b) && isProgression (b:c:cs)

-- Шестое задание
isFunction [] = True
isFunction p = map fst p == normalize (map fst p)

-- Седьмое задание
isSymmetric [] = True
isSymmetric p = x == length (normalize ((map fst p) ++ (map snd p))) where
                x = sum (map (\ a -> if fst a == snd a then 1 else 0) p)

-- Восьмое задание
isReflexive p = isReflexive' p where
                isReflexive' [] = True
                isReflexive' l@((a, b):bs) = (xIn (b, a) p) && isReflexive' bs

-- Девятое задание
closure p = normalize (p ++ closure' p) where
            closure' [] = []
            closure' l@((a, b):bs) = find' p ++ closure' bs
            find' [] = []
            find' ((a, b):bs) = map (\ (_, y) -> (a, y)) (findall' (a, b) ++ find' bs)
            findall' (a, b) = map (\ (_, y) -> (a, y)) (filter (\ (x, _) -> x == b) p)

-- Десятое задание
isTransitive p = sort p == sort (closure p)
