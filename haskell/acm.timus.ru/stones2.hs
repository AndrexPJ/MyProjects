import System.Random
import Data.List
import Data.Array

-- полный перебор всех подмножеств
bestSplit :: [Int] -> ([Int], Int)
bestSplit xs = bestSplit1 (subsequences xs) xs xs (sum xs)
  where
  bestSplit1 [] ys _ d = (ys, d)
  bestSplit1 (t:ts) ys xs d = let d1 = diff t xs
    in if d1 < d then bestSplit1 ts t xs d1 else bestSplit1 ts ys xs d
  diff subset set = abs(sum subset - sum (set \\ subset))

-- решение методом динамического программирования
-- http://en.wikipedia.org/wiki/Partition_problem
table :: Int -> Int -> [Int] -> Array (Int, Int) (Bool, [Int])
table m n xs = a  where
  a = array ((0,0), (m,n))
    ([((0, j), (True, [])) | j <- [0..n]] ++
    [((i, 0), (False, [])) | i <- [1..m]] ++
    [((i, j), if fst $ a!(i, j-1) then a!(i, j-1) else (let k = i - xs !! (j-1) in if k >= 0 && (fst $ a!(k, j-1)) then (True, (xs !! (j-1) : (snd $ a!(k, j-1)))) else (False, []))) | i <- [1..m], j <- [1..n]])

bestSubset :: Array (Int, Int) (Bool, [Int]) -> [Int]
bestSubset arr = last [ snd $ arr!(i, u1) | i <- [l0..u0], fst $ arr!(i, u1) ] where ((l0,_), (u0,u1)) = bounds arr

mySplit :: [Int] -> ([Int], Int)
mySplit xs = let
  n = length xs
  s = sum xs
  m = s `div` 2
  ys = bestSubset $ table m n xs
  s1 = sum ys
  s2 = s - s1
  in (ys, abs(s1 - s2))

-- случайный список из n целых чисел
randomlist :: Int -> StdGen -> [Int]
randomlist n = take n . unfoldr (Just . randomR (1, 1000))

showResult ys xs d = do
  let zs = xs \\ ys
  print $ sort ys
  print $ sum ys
  print $ sort zs
  print $ sum zs
  print d


readInt :: String -> Int
readInt = read 

main = do
  --seed  <- newStdGen
  --let xs = randomlist 20 seed
  -- лучший результат полным перебором
  --let (ys, d) = bestSplit xs
  --putStrLn "Brute-force solution:"
  --showResult ys xs d
  -- результат динамического программирования
  --let (ys', d') = mySplit xs
  --putStrLn "Pseudo-polinomial solution:"
  --showResult ys' xs d'
  _ <- getLine
  line <- getLine
  list <- return $ map (readInt) $ words line
  print $ snd $ mySplit list  


