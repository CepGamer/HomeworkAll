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
