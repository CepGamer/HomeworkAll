{-
 -Задание: Построить АВЛ дерево.
 -
-}

data Balance = L | M | R

data Tree = Tree Tree Ord Balance Tree | None

insert (Tree l a b r) x = 
