myfib n = myfib' n (0, 1)
  where
    myfib' 0 (a, _) = a
    myfib' 1 (_, b) = b
    myfib' x (a, b) = myfib' (x-1) (b, a + b)

mylen xs = sum [1 | _ <- xs]

myconcat [] bs = bs
myconcat (a:as) bs = a:(myconcat as bs)

myreverse as = myreverse' as []
  where
      myreverse' [] bs = bs
      myreverse' (a:as) bs = myreverse' as (a:bs)

mytake 0 (x:xs) = x
mytake a (x:xs) = mytake (a - 1) xs

mymap _ [] = []
mymap f (x:xs) = f x : mymap f xs

myunpack [] = []
myunpack (x:xs) = myconcat x $ myunpack xs

mydec as bs = [(a, b) | a<-as, b<-bs]

--(nominator, denom)

myred (a, b) = (div a d, div b d) where d = gcd a b
mymult (a, b) (c, d) = myred (a * c, b * d)
mydiv (a, b) (c, d) = mymult (a, b) (d, c)
mysum (a, b) (c, d) = myred (a * d + c * b, b * d)
mysub (a, b) (c, d) = mysum (a, b) (-c, d)

--(nominator, denom)

myshift n as = myconcat as (replicate n (0, 1))
mypad n as = myconcat (replicate n (0, 1)) as
mynorm as = [(a, b) | (a, b) <- as, a /= 0, b /= 1]
mydeg as = mylen (mynorm as) - 1

myzip _ [] [] = []
myzip op (a:as) (b:bs) = myconcat [op a b] (myzip op as bs)
myzip' op as bs = myzip op (mypad (-d) as) (mypad d bs)
  where d = (mylen as) - mylen bs

mydivpol as bs = mydiv' (mynorm as) (mynorm bs) []
  where mydiv' a s q | ddif < 0 = ()
                     | otherwise = mydiv' a' s q'
            where   ddif = (mydeg a) - (mydeg s)
                    k = mydiv (head a) (head s)
                    ks = map (mymult k) $ myshift ddif s
                    q' = myzip' (+) q $ myshift ddif [k]
                    a' = mynorm $ tail $ myzip' (-) a ks

myprint' (a, b) = "(" ++ show a ++ "/" ++ show b ++ ")"
myprint'' (a, b) = myprint' (a, b) ++ "x" ++ (if mydeg as /= 0 then "^" ++ show (mydeg as - 1) else "")
myprint ((a, b):as) = mymap myprint'' as
