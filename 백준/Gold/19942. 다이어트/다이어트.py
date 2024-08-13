from itertools import combinations

def find_min_cost(N, mp, mf, ms, mv, ingredients):
    min_cost = float('inf')
    best_combination = None

    for r in range(1, N + 1):
        for combo in combinations(range(N), r):
            p, f, s, v, cost = 0, 0, 0, 0, 0
            for idx in combo:
                p += ingredients[idx][0]
                f += ingredients[idx][1]
                s += ingredients[idx][2]
                v += ingredients[idx][3]
                cost += ingredients[idx][4]

            if p >= mp and f >= mf and s >= ms and v >= mv:
                if cost < min_cost:
                    min_cost = cost
                    best_combination = combo
                elif cost == min_cost:
                    best_combination = min(best_combination, combo)

    if best_combination is None:
        print(-1)
    else:
        print(min_cost)
        print(' '.join(str(idx + 1) for idx in best_combination))

N = int(input().strip())
mp, mf, ms, mv = map(int, input().strip().split())
ingredients = []
for _ in range(N):
    ingredients.append(list(map(int, input().strip().split())))

find_min_cost(N, mp, mf, ms, mv, ingredients)