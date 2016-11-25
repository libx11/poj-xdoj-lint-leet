a = b = c = d = e = f = 0
str = [i for i in input('enter a str') if i == '(' or i == ')' or i == '[' or i == ']' or i == '{' or i == '}']
for i in str:
	if i == '(':
		a += 1
	elif i == '[':
		b += 1
	elif i == '{':
		c += 1
	elif i == ')':
		d += 1
	elif i == ']':
		e += 1
	elif i == '}':
		f += 1
if a == d && b == e && c == f:
	for i in str:
...