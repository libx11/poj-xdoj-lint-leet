def tri(max):
    a = [1]
    while len(a) < max:
        yield a
        a.append(0)
        a = [a[i] + a[i-1] for i in range(len(a))]
for i in tri(int(input())):
    print(i)
