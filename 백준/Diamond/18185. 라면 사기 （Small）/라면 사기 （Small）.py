def buy_one_item(index): 
    global total_cost
    total_cost += 3 * quantities[index]

def buy_two_items(index): 
    global total_cost
    min_quantity = min(quantities[index:index+2])
    quantities[index] -= min_quantity
    quantities[index+1] -= min_quantity
    total_cost += 5 * min_quantity

def buy_three_items(index): 
    global total_cost
    min_quantity = min(quantities[index:index+3])
    quantities[index] -= min_quantity
    quantities[index+1] -= min_quantity
    quantities[index+2] -= min_quantity
    total_cost += 7 * min_quantity
    
import sys
input = sys.stdin.read
data = input().split()
N = int(data[0])
quantities = list(map(int, data[1:])) + [0, 0]
total_cost = 0

for i in range(N):
    if quantities[i+1] > quantities[i+2]: 
        min_quantity = min(quantities[i], quantities[i+1] - quantities[i+2])
        quantities[i] -= min_quantity
        quantities[i+1] -= min_quantity
        total_cost += 5 * min_quantity
        buy_three_items(i)
        buy_one_item(i)
    else:
        buy_three_items(i)
        buy_two_items(i)
        buy_one_item(i)

print(total_cost)