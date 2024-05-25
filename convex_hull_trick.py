import matplotlib.pyplot as plt
import random

class Line:
    def __init__(self, a, b):
        self.a = a
        self.b = b

    def f(self, x):
        return self.a * x + self.b

    def __str__(self):
        return f"f(x) = {self.a}x + {self.b}"

    def __repr__(self):
        return str(self)
    
    def intersection(self, other: "Line"):
        x = (other.b - self.b) / (self.a - other.a)
        return x, self.f(x)
    
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
        