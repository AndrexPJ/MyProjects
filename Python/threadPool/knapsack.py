def makeArray2D(fDim,sDim):
	array = [0] * fDim
	for i in range(fDim):
    		array[i] = [0] * sDim
	return array

def findQueue(k,s,D,weigths,stack):
	if (D[k][s] == 0) :
		return stack 
	if (D[k-1][s] == D[k][s]):
                while(D[k-1][s] == D[k][s]):
                        k-=1
		findQueue(k-1,s,D,weigths,stack)
	else :
		findQueue(k-1,s - weigths[k-1],D,weigths,stack)
		stack.append(k-1)
	return stack
		
	 

def packKnapsack(prices,weigths,count,max_weigth):
        if(len(prices) < count):
                count = len(prices)
	D = makeArray2D(count+1,max_weigth+1)
	for k in range(1,count+1):
		for s in range(max_weigth+1):
			if (s >= weigths[k-1]):
				D[k][s] = max(D[k-1][s],D[k-1][s-weigths[k-1]]+prices[k-1])
			else :
				D[k][s] = D[k-1][s]
	stack = []
        queue = findQueue(count,max_weigth,D,weigths,stack)
        #if(len(prices) < count):
        #        if(queue == []):
        #                return []
        #        else:
        #                return range(len(prices))
	return queue

	






