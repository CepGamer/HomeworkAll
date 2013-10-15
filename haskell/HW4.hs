data BT a = BT (BT a) a (BT a) | None

myinsert None a = BT None a None
myinsert (BT l a r) t
    | t > a    = BT l a $ myinsert r t
    | otherwise = BT (myinsert l t) a r

myfind None _ = Nothing
myfind x@(BT l a r) t
    | a == t    = Just x
    | t < a     = myfind l t
    | otherwise = myfind r t

elements None = []
elements (BT None a None) = [a]
elements b@(BT l a r) = els b [] where
	els (BT lx x rx) y = els lx $ x:els rx y
	els _ y = y


eqBST None None = True
eqBST (BT l a r) (BT lx x rx) = x == a && eqBST l lx && eqBST r rx
eqBST _ _ = False

isBST a = isBST' $ elements a where 
    isBST' (x:p@(y:ys)) = x <= y && isBST' p
    isBST' _ = True
