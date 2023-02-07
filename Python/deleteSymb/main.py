def sqr(k1,k2,k3,x):
    return k1 * x ** 2 + k2 * x + k3

def delete_symb(data, symb):
    mass = []
    for i in data:
        if i != symb:
            mass.append(i)
    return "".join(mass)

def square(h, osnovanie):
    return 0.5 * h * osnovanie

def circle(r):
    return 3.14 * r ** 2

def LIST_sum(data):
    p = 1
    summa = 0
    for i in list:
        summa += i * p
        p += 1
    return summa

def D(a,b,c):
    return b ** 2 - 4 * a * c

def x1(D,b,a):
    sol_1 = (D ** 0.5 + b)/ 2 * a
    sol_2 = (D ** 0.5 + b) / 2 * a
    return (sol_1, sol_2)

def equation(list, x):
    summ = 0
    for i in range(len(list)):
        if i == 0:
            summ = list[i]
        else:
            summ = summ + list[i] * x ** i

def palindrome(word):
    v1 = 0
    v2 = len(word)-1
    while (v2 - v1 > 2):
        if word[v1] != word[v2]:
            return False

def div_by_4(n):
    return (n % 100) % 4 == 0

def div_by_3(n):
    h = len(str(n))
    sum = 0
    for i in range (0,h):
        sum += n
        n = n / 10
    return sum % 3

def Rad(x,y):
    return sqr(x ** 2 + y ** 2)


