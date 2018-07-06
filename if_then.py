#new
#collect string / test length
'''input = raw_input("please enter a test string:")
if len(input) < 6:
	print ("your string is too short.")
	print ("please enter a string with at least 6 characters.")
'''
'''input = raw_input("please enter an integer:")
number = int(input)

if number % 2 == 0:
	print ("your number is even.")
else:
	print("your number is odd.")
'''
'''
a = int(raw_input("the length of side a = "))
b = int(raw_input("the length of side b = "))
c = int(raw_input("the length of side c = "))
if a != b and b != c and a != c :
	print("This is scalene triangle.")
elif a == b and b == c:
	print("This is an equilateral triangle.")
else:
	print("This is an isosceles triangle.")
'''
a = int(raw_input("Price of nim = "))
b = int(raw_input("price of rob = "))
c = int(raw_input("price of euro= "))
d = (a - 1255000)*20
e = (a - 1365000)*8
f = (a - 1355000)*11
#g = d + e + f
h = (b - 705000)*11
i = (c-9500)*2000
g = d + e + f + h + i 
print ('sod ='),g
k = (a*40) + (b*15) + (c*3000) + 7000000  
print k
