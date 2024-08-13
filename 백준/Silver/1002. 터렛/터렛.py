import math

def find_intersection_points(x1, y1, r1, x2, y2, r2):
    dist = math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)
    
    if dist == 0 and r1 == r2:
        return -1  # 무한대의 교차점
    elif dist == r1 + r2 or dist == abs(r1 - r2):
        return 1   # 접점 1개
    elif abs(r1 - r2) < dist < r1 + r2:
        return 2   # 교차점 2개
    else:
        return 0   # 교차점 없음

def main():
    import sys
    input = sys.stdin.read
    data = input().split()
    
    T = int(data[0])
    index = 1
    
    results = []
    for _ in range(T):
        x1 = int(data[index])
        y1 = int(data[index+1])
        r1 = int(data[index+2])
        x2 = int(data[index+3])
        y2 = int(data[index+4])
        r2 = int(data[index+5])
        result = find_intersection_points(x1, y1, r1, x2, y2, r2)
        results.append(result)
        index += 6
    
    for res in results:
        print(res)

if __name__ == "__main__":
    main()