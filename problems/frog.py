def mul(A, B):
    C = []
    for i in range(len(A)):
        C.append([])
        for j in range(len(B[0])):
            C[i].append(0)
            for k in range(len(B)):
                C[i][j] += A[i][k] * B[k][j]
                
    return C

def cw():
    return [
        [0, -1, 0],
        [1, 0, 0],
        [0, 0, 1]
    ]
    
def ccw():
    return [
        [0, 1, 0],
        [-1, 0, 0],
        [0, 0, 1]
    ]
    
def xflip(k):
    return [
        [-1, 0, 0],
        [0, 1, 0],
        [2 * k, 0, 1]
    ]

def yflip(k):
    return [
        [1, 0, 0],
        [0, -1, 0],
        [0, 2 * k, 1]
    ]
    
n, m, q = input().split()
n, m, q = int(n), int(m), int(q)
frog = []
matrix = []

for _ in range(n):
    frog.append(list(map(int, input().split())))
    
base = [[1, 0, 0], [0, 1, 0], [0, 0, 1]]
for _ in range(m):
    command = input().split()
    if command[0] == 'cw':
        base = mul(base, cw())
    elif command[0] == 'ccw':
        base = mul(base, ccw())
    elif command[0] == 'xflip':
        base = mul(base, xflip(int(command[1])))
    else:
        base = mul(base, yflip(int(command[1])))
        
    matrix.append(base)
    
for _ in range(q):
    x, y = map(int, input().split())
    res = mul([[*frog[x - 1], 1]], matrix[y - 1])
    print(f"{res[0][0]} {res[0][1]}")