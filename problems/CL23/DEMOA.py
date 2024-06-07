n = int(input())
s = input()

def process(s):
    cnt = 0
    cur = ''
    
    ret = ''
    
    for c in s:
        if c == cur:
            cnt += 1
        else:
            if cnt > 0:
                ret += str(cnt) + cur
            cnt = 1
            cur = c
            
    if cnt > 0:
        ret += str(cnt) + cur
        
    return ret
    
for _ in range(n):
    s = process(s)
    
print(s)