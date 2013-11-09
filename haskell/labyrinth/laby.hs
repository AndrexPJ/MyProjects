import System.Environment
import Control.Monad
import qualified Data.Map as Map

type TKey = (Int,Int)

loadLab :: String -> IO [String]
loadLab name = do
                   s <- Prelude.readFile name 
                   let lns = lines s
		   return lns

--------------------------------------
strToBool "1" = True
strToBool "0" = False
strToBool  _  = error "Bad input file!"

strToPair str i j = ((i,j),(strToBool str))

strToPairList str i = strToPairList' (words str) i 0
strToPairList' [] _ _ = []
strToPairList' (s:str) i j =  (strToPair s i j) : (strToPairList' str i (j+1))

fileStrToList strs = concat $ fileStrToList' strs 0
fileStrToList' [] _ = []
fileStrToList' (s:strs) i = (strToPairList s i) : (fileStrToList' strs (i+1))
--------------------------------------

--------------------------------------
elemCount mp = round $ sqrt $ fromIntegral $ Map.size mp
printCount mp = round $ sqrt $ sqrt $ fromIntegral $ Map.size mp
--------------------------------------

--------------------------------------
isNeighbour :: Int -> Map.Map TKey Bool -> Int  -> Bool
isNeighbour f mp s = if( Map.member (f,s) mp) then
		 	mp Map.! (f,s)
		     else False

neList el mp dict = Prelude.filter (isNeighbour el mp) dict


---список пар соседей для списка пар--
neListforList :: [(Int,[Int])] -> Map.Map TKey Bool ->[Int] -> [(Int,[Int])]
neListforList _ _ [] = []
neListforList [] _ _ = []
neListforList (el:ls) mp dict = do
				let f = fst el
				    neL = neList f mp dict
				    pList = Prelude.map (\n -> (n, f:(snd el)) ) neL
			        pList ++ (neListforList ls mp dict)
--------------------------------------

--------------------------------------
printLine :: Int -> IO()
printLine 0 = do
		putStrLn "" 
		return ()
printLine n = do
		putStr " ---"
		printLine (n-1)
		return ()
printVLine :: Int -> Int -> Map.Map TKey Bool -> IO ()
printVLine el ne mp = if isNeighbour el mp ne 
			then
				do 
				   putStr $ show el
				   putStr "   "
				   return ()
			else    
				do 
				   putStr $ show el
				   putStr " | "
				   return()
printGLine :: Int -> Int -> Map.Map TKey Bool -> IO ()
printGLine el ne mp = if isNeighbour el mp ne 
			then
				do 
				   putStr "    "
				   return ()
			else    
				do 
				   putStr " ---"
				   return()

printVStr :: Int -> Int -> Map.Map TKey Bool -> IO ()
printVStr i size mp = do
			let beg = (i*size) 
			    end = ((i*size) + size - 2)
			putStr "| "
			Prelude.mapM_ ( \n -> printVLine n (n+1) mp ) [beg..end]
			putStr $ show (end+1)
			putStr " |"
			putStrLn ""
			return ()

printGStr :: Int -> Int -> Map.Map TKey Bool -> IO ()
printGStr i size mp = do
			let beg = (i*size) 
			    end = ((i*size) + size - 1)
			Prelude.mapM_ ( \n -> printGLine n (n+size) mp ) [beg..end]
			putStrLn ""
			return ()
printPair :: Int -> Int -> Map.Map TKey Bool -> IO ()
printPair i size mp = do
		   	printVStr i size mp
		   	printGStr i size mp
			return ()
printLab :: Int -> Map.Map TKey Bool -> IO ()
printLab size mp = do
		      printLine size
		      Prelude.mapM_ ( \i -> printPair i size mp) [0..size - 2]
		      printVStr (size - 1) size mp
		      printLine size
		      return ()

testPrint = do 
	let l = [((0,1),True),((1,2),False),((3,4),False),((4,5),False),((6,7),False),((7,8),True),((0,3),True),((1,4),False),((2,5),False),((3,6),False),((4,7),False),((5,8),True)]
	printLab 3 (Map.fromList l)
	return ()
--------------------------------------

--------------------------------------
findPath :: Int -> Int -> Int -> Map.Map TKey Bool -> [Int]
makePath :: Int -> Map.Map TKey Bool -> [Int] -> [(Int,[Int])] -> [Int]
findPath f s size mp = reverse $ makePath s mp [0..(size-1)] [(f,[])]
makePath _ _ [] _ = []
makePath s mp dict buf = do 
			   let nl = neListforList buf mp dict
			       fnl = Prelude.map (fst) nl
			       newDict = Prelude.filter (\s -> not (elem s fnl) ) dict
		           if nl == [] then [] else
			   			if elem s fnl then s:(snd $ head $ Prelude.filter (\(n,ns) -> n == s) nl)
					 	else makePath s mp newDict nl
--------------------------------------

--------------------------------------
loadAndPrint :: IO ()
loadAndPrint = do
		 file <- loadLab "lab.txt"
		 let mp = Map.fromList $ fileStrToList file
		     psize = printCount mp
		     size = elemCount mp
		     loop = do
				printLab psize mp
				putStr "from(?) : "
				a <- getLine
				putStr "to(?) : "
				b <- getLine
		 		putStrLn $ show $ findPath (read a ::Int) (read b ::Int) size mp
				loop
		 loop
		 return ()
