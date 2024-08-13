import sys
input = sys.stdin.read
from collections import defaultdict

def dfs(k, adj, vst):
    vst[k] = True
    for e in adj[k]:
        if not vst[e]:
            dfs(e, adj, vst)

def main():
    input_data = input().split()
    idx = 0
    
    n = int(input_data[idx])
    m = int(input_data[idx + 1])
    idx += 2
    
    adj = defaultdict(list)
    
    for i in range(1, n + 1):
        for j in range(1, n + 1):
            x = int(input_data[idx])
            idx += 1
            if x == 1:
                adj[i].append(j)
    
    vst = [False] * (n + 1)
    cnt = 0
    
    for i in range(m):
        x = int(input_data[idx])
        idx += 1
        if not vst[x]:
            cnt += 1
            dfs(x, adj, vst)
    
    if cnt == 1:
        print("YES")
    else:
        print("NO")

if __name__ == "__main__":
    main()