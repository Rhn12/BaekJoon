import math

def distance(p1, p2):
    return math.sqrt((p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2)

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

def initial_clustering(cities, K):
    clusters = [[] for _ in range(K)]
    sorted_cities = sorted(range(len(cities)), key=lambda i: (cities[i][0], cities[i][1]))
    for i, city_idx in enumerate(sorted_cities):
        clusters[i % K].append(city_idx)
    return clusters

N, K = map(int, input().split())
cities = [tuple(map(int, input().split())) for _ in range(N)]

# 초기 클러스터링 (X좌표, Y좌표 순으로 정렬하여 K개 클러스터로 분할)
clusters = initial_clustering(cities, K)

# 각 클러스터에서 TSP 경로 계산
tours = []
for cluster in clusters:
    points = [cities[i] for i in cluster]
    tour = greedy_tsp(points)
    tours.append([cluster[i] + 1 for i in tour])

# 결과 출력
for tour in tours:
    print(len(tour), ' '.join(map(str, tour)))