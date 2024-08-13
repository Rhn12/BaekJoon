import sys, itertools

input=sys.stdin.readline
T=int(input())

for _ in range(T):
    N=int(input())
    points = []
    total_x,total_y = 0,0
 
    for _ in range(N):
        x,y = map(int,input().split())
        total_x +=x ; total_y += y
        points.append((x,y))
 
    comb = list(itertools.combinations(points, N//2))
    ans=3e5
    
    for c in comb[:len(comb)//2]:
        x1,y1 = 0,0
        for x,y in c:
            x1 += x ; y1 += y
        x2,y2 = total_x-x1,total_y-y1
        
        hab_vector = ((x2-x1)**2 + (y2-y1)**2)**(0.5)
        ans=min(ans,hab_vector)
    print(ans)