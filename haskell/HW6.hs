{-
    Hometask #6: Map.
    MadeBy: Bolotov Sergey.
-}

--               left      Pair     height  right
data Map a b = T (Map a b) (a, [b]) Integer (Map a b) | None

height None        = 0
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


empty = None

insert (key, val) None = T None (key, [val]) 1 None
insert pair@(key, val) (T l (k, v) h r)
    | key > k = balance $ insert pair r
    | key < k = balance $ insert pair l
    | otherwise = T l (k, val:v) h r

find _ None = Nothing
find key (T l (k, v) _ r)
    | key > k = find key r
    | key < k = find key l
    | otherwise = Just v

remove _ None = None
remove key (T l (k, v) h r)
    | key > k = balance $ remove key r
    | key < k = balance $ remove key l
    | otherwise = 
        case v of
            x:xs -> T l (key, xs) h r
            x:[] -> case r of
                        None -> l
                        _ -> T l k' h r' where
                                k' = findMin r
                                findMin (T None a _ r) = a
                                findMin (T l _ _ _) = findMin l
                                r' = rmMin r
                                rmMin (T None _ _ r) = r
                                rmMin (T l a _ r) = balance $ T (rmMin l) a 0 r

--fold fun map acc = 

showTree None = "None"
showTree (T l (a, as) h r) = "(T " ++ showTree l ++ " (" ++ show a ++ ", " ++ show as ++ ") " ++ show h ++ " " ++ showTree r ++ ")"

--makeTreeList (a:as) = foldl (\acc x -> insert x acc) (T None a 1 None) as

elements b = els b [] where
    els (T l x _ r) y = els l $ x:els r y
    els _ y = y
