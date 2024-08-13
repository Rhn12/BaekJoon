import math

# Constants
X_MIN, X_MAX = -10, 10
Y_MIN, Y_MAX = -20, 20
STEP = 0.1
EPS = 1e-5
INF = float('inf')

def sq(x):
    return x ** 2

def radiation(islands, x, y):
    res = 0
    for island in islands:
        dist_squared = sq(x) + sq(y - island)
        if dist_squared < EPS:
            return INF
        res += 1 / dist_squared
    return res

def y_2dot(islands, x, y, y_dot):
    ds_sq = 1 + sq(y_dot)
    sum_radiation = 1  # natural radiation
    sum_first_term = 0
    sum_second_term = 0

    for island in islands:
        dist_sq = sq(x) + sq(y - island)
        sum_radiation += 1 / dist_sq
        sum_first_term += (x + (y - island) * y_dot) / sq(dist_sq)
        sum_second_term += (y - island) / sq(dist_sq)

    return 2 * ds_sq * (sum_first_term * y_dot - sum_second_term * ds_sq) / sum_radiation

def rk(islands, x, y, y_dot):
    res = 0
    for i in range(int((X_MAX - X_MIN) / STEP)):
        if y < Y_MIN or y > Y_MAX:
            return (INF, y)
        
        res += STEP * (1 + radiation(islands, x, y)) * math.sqrt(1 + sq(y_dot))
        k1 = STEP * y_dot
        l1 = STEP * y_2dot(islands, x, y, y_dot)
        
        # Update values (RK1 for simplicity in this translation)
        x += STEP
        y += k1
        y_dot += l1

    return (res, y)

def solve():
    n, a, b = map(float, input().split())  # Ensure to capture n as float if needed, otherwise change accordingly
    islands = list(map(float, input().split()))
    initial_y_dot = [-2, 2] + [(island - a) / 10 for island in islands]
    initial_y_dot.sort()

    ans = INF
    for i in range(1, len(initial_y_dot)):
        l, r = initial_y_dot[i - 1], initial_y_dot[i]
        tmp = INF
        while abs(r - l) > EPS:
            m = (l + r) / 2
            res, y = rk(islands, X_MIN, a, m)
            if y >= b:
                r = m
            else:
                l = m
            tmp = res
        ans = min(ans, tmp)
    return ans

if __name__ == "__main__":
    t = int(input())
    for tc in range(1, t + 1):
        print(f"Case #{tc}: {solve():.10f}")