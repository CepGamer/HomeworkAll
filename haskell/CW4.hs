data BT a = BT a (BT a, BT a) | Empty

nnodes Empty = 0
nnodes (BT a (x, y)) = 1 + nnodes x + nnodes y

nleaves Empty = 0
nleaves (BT _ (Empty, Empty)) = 1
nleaves (BT _ (a, b)) = nleaves a + nleaves b

depth Empty = 0
depth (BT _ (a, b)) = 1 + max (depth a) (depth b)

leaves = leaves' [] where
    leaves' acc Empty = acc
    leaves' acc (BT a (Empty, Empty)) = a:acc
    leaves' acc (BT a (x, y)) = leaves' (leaves' acc x) y

nodes = nodes' [] where
    nodes' acc Empty = acc
    nodes' acc (BT a (x, y)) = nodes' (nodes' (a:acc) x) y

maxn a = (nodes a) -- Найти максимум для списка просто.

factor n Empty  = (0, 0)
factor n (BT a (l, r)) = (ll + lr + x, gel + ger + y) where
  (x, y) = if a < n then (1, 0) else (0, 1)
  (ll, gel) = factor n l
  (lr, ger) = factor n r
