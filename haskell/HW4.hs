data BT a = BT a (BT a, BT a) | None

myinsert None a = BT a (None, None)
myinsert (BT a (b, c)) t
    | t <= a    = BT a (myinsert b t, c)
    | otherwise = BT a (b, myinsert c t)

--(BT 8 (BT 4 (BT 3 (BT 2 (None, None), None), BT 5 (None, None)), BT 10 (BT 9 (None, None), None)))

myfind None _ = Nothing
myfind x@(BT a (b, c)) t
    | a == t    = Just x
    | t < a     = myfind b t
    | otherwise = myfind c t

isBST (BT a (b, c)) = isBST' b && isBST' c where
    isBST' (BT _ (None, None)) = True
    isBST' (BT a (BT b _, BT c _)) = (b <= a) && (c > a)

elements None = []
elements (BT a (None, None)) = [a]
elements (BT a (b, c)) = elements b ++ [a] ++ elements c

eqBST None None = True
eqBST (BT a (b, c)) (BT x (y, z)) = x == a && eqBST b y && eqBST c z
eqBST _ _ = False
