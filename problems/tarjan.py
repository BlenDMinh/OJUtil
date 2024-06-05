n, m = input().split()
n, m = int(n), int(m)

graph = [[] for _ in range(n + 1)]

for _ in range(m):
    u, v = input().split()
    u, v = int(u), int(v)
    graph[u].append(v)


time = 0

state = [0 for _ in range(n + 1)]
num = [0 for _ in range(n + 1)]
low = [0 for _ in range(n + 1)]
stack = []

res = 0

def tarjan(u):
    global time, res
    time += 1
    num[u] = low[u] = time
    state[u] = 1
    stack.append(u)
    
    for v in graph[u]:
        if state[v] == 0:
            tarjan(v)
        if state[v] == 1:
            low[u] = min(low[u], low[v])
    
    if(low[u] == num[u]):
        res += 1
        while True:
            v = stack.pop()
            state[v] = 2
            if v == u:
                break
            
for i in range(1, n + 1):
    if state[i] == 0:
        tarjan(i)
        
print(res)