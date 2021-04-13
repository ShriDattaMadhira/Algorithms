def sol_trace(n,k,m,i):
    if i == 0:
        return
    sol_trace(n,k,m,i-1)
    print("Floor:",m[i][k])
    
def jar_ladder(n,k):
    eggFloor = [[0 for j in range(k+1)] for i in range(n+1)]
    temp = 0
    for i in range(1, n + 1): 
        for j in range(1, k + 1):
            eggFloor[i][j] = 1 + eggFloor[i-1][j] + eggFloor[i-1][j-1]
        if eggFloor[i][j] >= n:
            return i, eggFloor
            
n = 36
k = 2
minT, m = jar_ladder(n,k)
print(minT)
sol_trace(n,k,m,minT)