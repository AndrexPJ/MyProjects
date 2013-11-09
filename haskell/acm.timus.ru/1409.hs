main = do
  	 [a, b] <- (map read . words) `fmap` getLine
  	 print $ ( (show a) ++ (show b) )

	
