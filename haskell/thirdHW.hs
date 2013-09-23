myfib = 0 : scanl (+) 1 myfib
myfib' = 0 : 1 : zipWith (+) myfib' (tail myfib')

mylistmod _ [] = True
--mylistmod a (b:_) where a < b = True
mylistmod a (b:bs) = (a < b*b) || ((mod a b /= 0 ) && (mylistmod a bs))

myprime = 2 : 3 : [x | x <- [5, 7..], mylistmod x myprime]
