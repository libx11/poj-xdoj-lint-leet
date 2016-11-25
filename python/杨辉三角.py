def tri(max):
    N = [1]
    while len(N) <= max:
        yield (N)
        N.append(0)
        N = [N[i-1] + N[i] for i in range(len(N))]
for i in tri(int(input())):
    print (i)
