import math

def main():
    n = int(input())
    count = 8
    
    for i in range(1, n+1):
        if n - math.pow(2, i) == 0:
            count = count + i + 2
            break
        elif n - math.pow(2, i) < 0:
            count = count + i + 1
            break
    
    print(count)

if __name__ == "__main__":
    main()