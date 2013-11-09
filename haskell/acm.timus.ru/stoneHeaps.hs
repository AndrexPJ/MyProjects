import Data.List

readInt :: String -> Int
readInt = read 
 
rec h1 h2 [] = abs (h1 - h2)
rec h1 h2 (s:stones) =  min h3 h4
			where	
			     h3 = rec (h1+s) h2 stones   
			     h4 = rec h1 (h2+s) stones


rec' h1 h2 [] = abs (h1 - h2)
rec' h1 h2 stones = minimum $ map (\s -> rec (h1-s) (h2+s) (stones\\[s]) ) stones

main = do
 	  _ <- getLine
	  line <- getLine
          list <- return $ map (readInt) $ words line
	  print $ rec' (sum list)  0 list


