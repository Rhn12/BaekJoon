from collections import deque

def can_reach_with_cost_limit(N, graph, A, B, cost_limit, C):
    visited = [False] * (N + 1)
    queue = deque([(A, 0)])
    visited[A] = True
    while queue:
        current, cost = queue.popleft()
        if current == B:
            return True
        for neighbor, weight in graph[current]:
            if not visited[neighbor] and weight <= cost_limit:
                if cost + weight <= C:
                    queue.append((neighbor, cost + weight))
                    visited[neighbor] = True
    return False

def find_min_max_cost(N, M, A, B, C, edges):
    graph = [[] for _ in range(N + 1)]
    max_cost = 0
    for u, v, w in edges:
        graph[u].append((v, w))
        graph[v].append((u, w))
        max_cost = max(max_cost, w)
    left, right = 0, max_cost
    result = -1
    while left <= right:
        mid = (left + right) // 2
        if can_reach_with_cost_limit(N, graph, A, B, mid, C):
            result = mid
            right = mid - 1
        else:
            left = mid + 1
    return result

N, M, A, B, C = map(int, input().split())
edges = [tuple(map(int, input().split())) for _ in range(M)]

result = find_min_max_cost(N, M, A, B, C, edges)
print(result)