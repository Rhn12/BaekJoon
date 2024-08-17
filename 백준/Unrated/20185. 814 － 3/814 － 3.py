import math

# 유클리드 거리 계산 함수
def distance(p1, p2):
    return math.sqrt((p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2)

# Greedy 방식으로 순회 경로 찾기
def greedy_tsp(points):
    n = len(points)
    visited = [False] * n
    tour = [0]
    visited[0] = True
    
    for _ in range(1, n):
        last = tour[-1]
        next_city = min(
            [(distance(points[last], points[i]), i) for i in range(n) if not visited[i]]
        )[1]
        tour.append(next_city)
        visited[next_city] = True
    
    return tour

# 입력 처리
N, K = map(int, input().split())
cities = [tuple(map(int, input().split())) for _ in range(N)]

# 초기 K개 클러스터로 분할 (여기서는 간단히 K등분)
clusters = [[] for _ in range(K)]
for i in range(N):
    clusters[i % K].append(i)

# 각 클러스터에서 TSP 문제 해결
tours = []
for cluster in clusters:
    points = [cities[i] for i in cluster]
    tour = greedy_tsp(points)
    tours.append([cluster[i] + 1 for i in tour])

# 결과 출력
for tour in tours:
    print(len(tour), ' '.join(map(str, tour)))