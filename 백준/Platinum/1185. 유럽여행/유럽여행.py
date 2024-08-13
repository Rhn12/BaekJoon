import sys
from heapq import heappop, heappush

class DisjointSet:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n

    def find(self, u):
        if self.parent[u] != u:
            self.parent[u] = self.find(self.parent[u])
        return self.parent[u]

    def union(self, u, v):
        u_root = self.find(u)
        v_root = self.find(v)
        if u_root != v_root:
            if self.rank[u_root] > self.rank[v_root]:
                self.parent[v_root] = u_root
            else:
                self.parent[u_root] = v_root
                if self.rank[u_root] == self.rank[v_root]:
                    self.rank[v_root] += 1

def kruskal(country_num, edges):
    edges.sort()
    ds = DisjointSet(country_num + 1)
    min_spanning = 0
    union_count = 0

    for cost, u, v in edges:
        if ds.find(u) != ds.find(v):
            ds.union(u, v)
            min_spanning += cost
            union_count += 1
            if union_count == country_num - 1:
                break

    return min_spanning

def main():
    input = sys.stdin.read
    data = input().split()

    country_num = int(data[0])
    path_num = int(data[1])
    
    country_cost = [0] * (country_num + 1)
    idx = 2
    min_country_cost = float('inf')
    
    for i in range(1, country_num + 1):
        country_cost[i] = int(data[idx])
        min_country_cost = min(min_country_cost, country_cost[i])
        idx += 1
    
    edges = []
    
    for _ in range(path_num):
        u = int(data[idx])
        v = int(data[idx + 1])
        weight = int(data[idx + 2])
        cost = 2 * weight + country_cost[u] + country_cost[v]
        edges.append((cost, u, v))
        idx += 3

    min_spanning = kruskal(country_num, edges)
    answer = min_spanning + min_country_cost
    print(answer)

if __name__ == '__main__':
    main()