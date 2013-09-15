mygcd x 0 = x
mygcd x y = mygcd y (mod x y)

iscoprime x y = (mygcd x y) == 1

euler n = length ( [x | x <- [1..(n - 1)], iscoprime x n ] )
