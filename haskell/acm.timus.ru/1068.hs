readInt :: String -> Int
readInt = read 
 



getSum n = if n > 0 then sum $ [1..n]
           else (-1) * (sum $ [1..(abs n)]) + 1

main = do
 	  n <-  getLine
	  print $ getSum $ readInt n  
