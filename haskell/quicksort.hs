import Data.List

quickSort [] = []
quickSort (head:tail) = quickSort listA ++ [head] ++ quickSort listB
		        where (listA,listB) = partition (\x -> x <= head) tail 


