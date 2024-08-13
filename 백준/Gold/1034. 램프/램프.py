def count_on_rows_after_switch(lamps, n, m, k):
    max_on_rows = 0

    for row in lamps:
        zero_count = row.count('0')
        if zero_count <= k and (k - zero_count) % 2 == 0:
            similar_rows = lamps.count(row)
            max_on_rows = max(max_on_rows, similar_rows)
    
    return max_on_rows

if __name__ == "__main__":
    n, m = map(int, input().split())
    lamps = [input().strip() for _ in range(n)]
    k = int(input())
    
    result = count_on_rows_after_switch(lamps, n, m, k)
    print(result)