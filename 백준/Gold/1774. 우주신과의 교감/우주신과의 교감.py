import sys
import math
input = sys.stdin.readline

class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n

    def find(self, u):
        if self.parent[u] != u:
            self.parent[u] = self.find(self.parent[u])
        return self.parent[u]

    def union(self, u, v):
        rootU = self.find(u)
        rootV = self.find(v)
        if rootU != rootV:
            if self.rank[rootU] > self.rank[rootV]:
                self.parent[rootV] = rootU
            elif self.rank[rootU] < self.rank[rootV]:
                self.parent[rootU] = rootV
            else:
                self.parent[rootV] = rootU
                self.rank[rootU] += 1

def euclidean_distance(x1, y1, x2, y2):
    return math.sqrt((x1 - x2) ** 2 + (y1 - y2) ** 2)

N, M = map(int, input().split())
points = [tuple(map(int, input().split())) for _ in range(N)]

edges = []
for _ in range(M):
    u, v = map(int, input().split())
    u -= 1
    v -= 1
    edges.append((0, u, v))

for i in range(N):
    for j in range(i + 1, N):
        dist = euclidean_distance(points[i][0], points[i][1], points[j][0], points[j][1])
        edges.append((dist, i, j))

edges.sort()
uf = UnionFind(N)
total_cost = 0
for dist, u, v in edges:
    if uf.find(u) != uf.find(v):
        uf.union(u, v)
        total_cost += dist

print(f"{total_cost:.2f}")