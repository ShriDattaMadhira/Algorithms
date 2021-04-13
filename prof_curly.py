def curly(i):
    if i >= N-1:
        return 0
##    print("i:",i)
    for j in range(N-1,i,-1):
##        print("J:",j)
        for k in range(i+1,j+1):
##            print("K:",k)
            d = T[i][k] + curly(k)
            if d < dist[i][j]:
                dist[i][j] = d
                s[i][j] = k
    return dist[i][j]

def getCost(i,j,cost):
    path.append(s[i][j])
    cost += dist[i][j]
    if s[i][j] < N-1:
        getCost(s[i][j],j,cost)
    return cost

T = [[0, 4, 2, 3, 5],
     [-99, 0, 1, 2, 3],
     [-99, -99, 0, 2, 4],
     [-99, -99, -99, 0, 1],
     [-99, -99, -99, -99, 0]]
N = 5
dist = [[999 for j in range(N)] for i in range(N)]
for i in range(N):
    dist[i][i] = 0
s = [[-99 for j in range(N)] for i in range(N)]
for i in range(N):
    s[i][i] = 0
i = 0
j = 4
cost = curly(i)
##print(s)
##print(dist)
path = []
path.append(i)
cost=0
c=getCost(i,j,cost)
print(path)
print(c)
