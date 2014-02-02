
type Array a = Int -> a


addPattern func input output = \i -> if i == input then output : func i 
									 	else func i


newArray value = \i -> [value]

addElem array index value = addPattern array index value

addElems [] array = array
addElems (pair:pairs) array = addElems  pairs  $ addElem array i v
								where (i,v) = pair 

main = do
	let array = newArray (-1)
	let array' = addElems  (map (\i -> (i,i*121)) [2..1000]) $ addElems  (map (\i -> (i,i+1)) [1..1000]) array
	print "ok"
	print $ array' 1
	print $ array' 2