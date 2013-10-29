{-
    Hometask #5, AVL-trees
    MadeBy: Bolotov Sergey
-}

--	            left     key height  right
data Tree a = T (Tree a) a   Integer (Tree a) | None

height None	       = 0
height (T _ _ h _) = h

balFactor (T l _ _ r) = height r - height l

--retHeight None = error "Cannot do this!"
retHeight (T l a _ r) = T l a (max (height l) (height r) + 1) r

rotR (T (T ll al _ rl) a _ r) = retHeight $ T ll al 0 $ retHeight $ T rl a 0 r

rotL (T l a _ (T lr ar _ rr)) = retHeight $ T (retHeight $ T l a 0 lr) ar 0 rr

balance q@(T l a _ r) = case balFactor q of
    2         -> rotL (T l a 0 (if balFactor r < 0 then rotR r else r))
    -2        -> rotR (T (if balFactor l > 0 then rotL l else l) a 0 r)
    otherwise -> retHeight q

insert a None = (T None a 1 None)
insert a (T l k h r)
    | a == k    = error "This key exists"
    | a < k     = balance (T (insert a l) k h r)
    | otherwise = balance (T l k h (insert a r))


showTree None = "None"
showTree (T l a h r) = "(T " ++ (showTree l) ++ " " ++ (show a) ++ " " ++ (show h) ++ " " ++ (showTree r) ++ ")"

makeTreeList (a:as) = foldl (\acc x -> insert x acc) (T None a 1 None) as

elements b = els b [] where
    els (T l x _ r) y = els l $ x:els r y
    els _ y = y
