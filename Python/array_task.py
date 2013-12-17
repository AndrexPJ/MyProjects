from random import randint
import sys

######################################################
def func(a):
	return pow(a,5)

def func2(a):
	if (a >= 0): 
		return a
	return 1

def find_not_paired_nums(array):
	xor = 0
	xorf = 0
	xorf2 = 0

	mn = min(array)
	shift = abs(mn) + 2

	mul = 1
   
	for i  in range(len(array)):
		xor ^= (array[i] + shift)
		#xorf ^= func(array[i])
	###### solves problem with sign of number #######
		#xorf2 ^= func2(array[i])
	###### ################################## #######

	for a in array:
		el = a + shift
		if ((mul % el) == 0):
			mul /= el
		else :
			mul *= el
	print (map(lambda x : x+shift,array))
	for i in range(len(array)):
		a = array[i] + shift
		b = (array[i] + shift) ^ xor
		#if ((func(b)  == xorf ^ func(a)) and (func2(b)  == xorf2 ^ func2(a)) ):
		#	return (a,b)
		print "mul: " + str(mul) + " a*b: " + str(a*b)
		if  ((a * b) == mul):
			return (a - shift,b - shift)
######################################################



def answer_check(p1,p2):
	(a,b) = p1
	p3 = (b,a)
	return ((p1 == p2) or (p3 == p2))


def get_test_array(count):
	a = randint(-10,10)
	b = randint(-10,10)
	while(b == a):
		b = randint(-10,10)
	pre_res = map(lambda x: randint(-10,10),range((count - 2)/2))
	res = pre_res + pre_res
	res.append(a)
	res.append(b)
	return ((a,b),res)

final_answ = True

step = 0
for j in range(100000):
	for i in range(100000):
		print step
		(pair,arr) = get_test_array(10)
		answ = find_not_paired_nums(arr) 
		pre = answer_check(pair,answ)
		if(not pre):
			print str(pair) + " " + str(answ) + " " + str(arr)
			exit()
		final_answ &= answer_check(pair,answ)
		step +=1

print final_answ

