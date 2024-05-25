import matplotlib.pyplot as plt

class Line:
    def __init__(self, a = 0, b = 0):
        self.a = a
        self.b = b

    def eval(self, x):
        return self.a * x + self.b

    def __str__(self):
        return f"f(x) = {self.a}x + {self.b}"

    def __repr__(self):
        return str(self)
    
    def intersection(self, other: "Line"):
        x = (other.b - self.b) / (self.a - other.a)
        return x, self.f(x)
    
class HullTrick:
    def __init__(self, N = 100000, is_min_hull = True, reverse = True) -> None:
        self.is_min_hull = is_min_hull
        self.reverse = reverse
        self._N = N
        self.size = 0
        self.lines = [Line(0, 0) for _ in range(N)]
        self.operations = []
        
    def __add_compare(l1: Line, l2: Line, l3: Line) -> bool:
        return l1.intersection(l3)[0] >= l1.intersection(l2)[0]
    def __add_compare_reverse(l1: Line, l2: Line, l3: Line) -> bool:
        return l1.intersection(l3)[0] <= l1.intersection(l2)[0]
    
    def __get_add_comparer(self):
        if self.is_min_hull:
            return self.__add_compare if not self.reverse else self.__add_compare_reverse
        
        return self.__add_compare if self.reverse else self.__add_compare_reverse 
    
    def comparer(x, y):
        return x < y
    
    def comparer_reverse(x, y):
        return x > y
    
    def __get_comparer(self):
        if self.is_min_hull:
            return self.comparer if not self.reverse else self.comparer_reverse
        return self.comparer if self.reverse else self.comparer_reverse
        
    def add(self, line: Line):
        if self.size < 2:
            self.lines[self.size] = line
            self.operations.append((self.size, self.size, self.lines[self.size]))
            self.size += 1
            return

        comparer = self.__get_add_comparer()
        L = 1
        R = self.size - 1
        POS = self.size
        while L < R:
            M = (L + R) // 2
            if comparer(self.lines[M - 1], self.lines[M], line):
                POS = M
                L = M + 1
            else:
                R = M
        
        self.operations.append((POS, self.size, self.lines[POS]))
        self.size = POS + 1
        self.lines[POS] = line
        
    def rollback(self):
        if len(self.operations) == 0:
            return
        op = self.operations[-1]
        self.size = op[0]
        self.lines[op[0]] = op[2]
        self.operations.pop()

    def get(self, x):
        comparer = self.__get_comparer()
        L = 0
        R = self.size - 1
        res = self.lines[L].eval(x)
        while L < R:
            M = (L + R) // 2
            e1 = self.lines[M].eval(x)
            e2 = self.lines[M + 1].eval(x)
            if comparer(e1, e2):
                L = M + 1
            else:
                R = M
                
            res = min(res, e1, e2) if self.is_min_hull else max(res, e1, e2)
    
def plot_lines(lines: list[Line]):
    x = [-500, 500]
    plt.ylim(-500, 500)
    for line in lines:
        y = [line.f(x[0]), line.f(x[1])]
        plt.plot(x, y, label=str(line))
    plt.legend()
    plt.show()

lines = [Line(0, 0), Line(-21, 542), Line(-20, 206)]
plot_lines(lines)

stack: list[Line] = []
lines.sort(key=lambda line: line.a, reverse=True)
print(lines)

for line in lines:
    if len(stack) < 2:
        stack.append(line)
        continue
    while len(stack) >= 2:
        l1 = stack[-2]
        l2 = stack[-1]
        l3 = line
        
        if l1.intersection(l3)[0] > l1.intersection(l2)[0]:
            break
        stack.pop()
    
    stack.append(line)
    
plot_lines(stack)
        