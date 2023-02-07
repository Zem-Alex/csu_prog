class Test3:
    def __init__(self, a = 20):
        print("")

class Test6:
        def b(self):
                return "T"

#obj6 = Test6
#Test6.b(obj6) // obj6.b() - тоже самое


class Complex:
    def __init__(self, a = 0, b = 0):
        self.a = a
        self.b = b
        #print(self.a, self.b)
    def __add__(self, other):
        return Complex(self.a + other.a, self.b + other.b)
    def __mul__(self, other):
        return Complex(self.a * other.a - self.b * other.b, self.a * other.b + self.b * other.a)
    def __repr__(self):
        return '({}, {})'.format(self.a, self.b)
    def __str__(self):
        return '({}, {})'.format(self.a, self.b)

#a = Complex(1, 1)
#other = Complex(1,2)
#print(Complex.add(a,other))
#print(Complex.mult(a,other))
#print(a * other)

def BubbleSort(listik):
    N = len(listik)
    for i in range(N - 1):
        for j in range(N - i - 1):
            if listik[j] > listik[j + 1]:
                buff = listik[j]
                listik[j] = listik[j + 1]
                listik[j + 1] = buff

listik = [2, 5, 7, 3, 1,9, 0]
#listik.sort()
print(listik)
BubbleSort(listik)
print(listik)

