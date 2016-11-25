str = []
for i in input('enter a str\n'):
	if i == '(' or i == '{' or i == '[':
		str.append(i)
	elif (i == ')' and str[-1] == '(') or (i == ']' and str[-1] == '[') or (i == '}' and str[-1] == '{'):
		str.pop()
if str == []:
	print('yes')
else:
	print('no')