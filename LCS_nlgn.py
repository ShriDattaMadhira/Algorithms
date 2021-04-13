import math

array = [9,3,10,1,18,6,4,7,13,8,14,15,16,17]
# array = [9,28,8,30,26,40,36,50,90,1]
m = [array[0]]
for i in range(1, len(array)):
    print(m)
    if array[i] > m[-1]:
        m.append(array[i])
    elif array[i] <= m[0]:
        if i != len(array)-1:
            m[0] = array[i]
    else:
        start, end = 0, len(m)-1
        while start <= end:
            mid = math.ceil((start+end)/2)
            if array[i] <= m[mid]:
                end = mid-1
            else:
                start = mid+1
        
        m[start] = array[i]

print(m)
print(len(m))