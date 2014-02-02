from pylab import *
import random


def q_sort(f_x_i,x_i,n,sign):
	indx_f_x_i = []
	res = f_x_i

	for i in range(n):
			indx_f_x_i.append(int(round(x_i[i] - sign*f_x_i[i])))

	for i in range(n):
		temp = res[i-indx_f_x_i[i]-1]
		res[i-indx_f_x_i[i]-1] = res[i]
		res[i] = temp

	return res



def xm_sort(f_x_i,x_i,n):
	res  = q_sort(f_x_i,x_i,n,1)
	#res1 = res[0:n/2]
	#res2 = res[n/2:n]

	for i in range(n): ##### O(n^2)
		res = q_sort(res,x_i,n,1)
		#res = q_sort(res[::-1],x_i,n,-1)[::-1]
		#res2 = q_sort(res2,x_i,n/2)

	#res = res1 + res2
	return res


arr = []
n = 1024

for i in range(n):
	arr.append(random.randint(-10,600))
	#arr.append(random.randint(1000,5000))

arr_max = max(arr)
arr_min = min(arr)

x = map(lambda i : float(i)/(n-1),range(n))
f_x = map(lambda f_i: (float(f_i)-arr_min)/(arr_max-arr_min), arr)

sorted_f_x = sort(f_x)

plot(x,f_x,'rd')

res = xm_sort(f_x,x,n)

plot(x,sorted_f_x,'b')
plot(x,res,'gd')
show()

