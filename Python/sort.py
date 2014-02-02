array = [13,123, 3, 2, 1001]

or_value =  reduce(lambda x,y : x^y, array)

mask = 1

or_value2 = or_value

arr_forw = []

for a in array:
	arr_forw.append(or_value)
	or_value^=a
	

arr_backw = []
print "=="
for a in array[::-1]:
	arr_backw.append(or_value2)
	or_value2^=a

##arr_backw = arr_backw[::-1]

for i in range(0,len(array)):
	print arr_backw[i] ^ arr_forw[i]