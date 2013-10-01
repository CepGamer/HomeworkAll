{- Haskell - язык строгой типизации. И автоматической. Если он не может сам определить тип - скорее
всего вы сделали ошибку. Типы "нестандартные": алгебраические, конструкторы (a -> b, a и b - типы).
Cтрелка имеет правую ассоциативность (скобки справа). Есть также unit ( () ), но он встроенный. -}
-- Алгебраический тип: имя типа = конструктор | конструктор...
data Color = Red | Green | Blue
colors = [Red, Green, Blue]

-- К слову о pattern matching
whichColor f = case f of
                 Red -> "Red"
                 Green -> "Green"
                 Blue -> "LaL"

colorsString = map whichColor colors

-- Конструктор
data Sound = Sound Int Int
sounds = [(Sound i) j | i <- [1..4], j <- [5..8]]
_ = map (Sound 1) [3..5]    --  Что это?

inRange s@(Sound _ f) = f >= 20 && f <= 20000

--  Тип м.б. рекурсивен

data Lal = Lal Int Lal

--  С малой буквы - неизвестно во время компиляции. С большой - известно. Аналог списка типа а:
data L a = Cons a (L a) | Nil

--  Список в Хаскелле таков (да, он где-то там определён, а не встроен):
--  data List a = a ':' (L a) | []

len' Nil = 0
len' (Cons _ l) = len' l + 1

{- Не знаю, что это
_ = [()]
_ = ["a"]
_ = [[]]
_ = [((), ())] -}

{-
Домашнее задание:
На дереве BT a = BT a (BT a) (BT a):
1. Вставка в дерево (дерево двоичного поиска).
insert :: BT Int -> Int -> BT Int

2. data Maybe a = Just a | Nothing
На дереве написать поиск, который возвращает Maybe
find :: BT Int -> Int -> Maybe (BT Int)

3. Проверить, является ли дерево деревом двоичного поиска.
isBST :: BT Int -> Bool

4. Сортированый по возрастанию список из вершин дерева.
elements :: BT Integer -> [Integer]
Не забудь отправить на почту!
-}
