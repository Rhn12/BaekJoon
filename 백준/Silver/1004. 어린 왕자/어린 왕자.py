import math

class Circle:
    def __init__(self, cx, cy, r):
        self.cx = cx
        self.cy = cy
        self.r = r

    def is_inside(self, x, y):
        dx = x - self.cx
        dy = y - self.cy
        return dx * dx + dy * dy < self.r * self.r

def count_crossings(x1, y1, x2, y2, circles):
    count = 0
    for circle in circles:
        start_inside = circle.is_inside(x1, y1)
        end_inside = circle.is_inside(x2, y2)
        if start_inside != end_inside:
            count += 1
    return count

def main():
    T = int(input())
    for _ in range(T):
        x1, y1, x2, y2 = map(int, input().split())
        n = int(input())
        circles = [Circle(*map(int, input().split())) for _ in range(n)]
        print(count_crossings(x1, y1, x2, y2, circles))

if __name__ == "__main__":
    main()