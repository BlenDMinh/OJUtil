import math

t = int(input())
for _ in range(t):
    a, b = map(int, input().split())
    
    if a == 0:
        print("NO SOL")
        continue
    
    closest = math.ceil(math.sqrt(a))
    
    need = closest ** 2 / a
    cloest_b = math.ceil(b / need)
    need *= math.pow(math.ceil(math.sqrt(cloest_b)), 2)
    
    print(need)