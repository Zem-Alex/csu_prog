def square(arg):
    P = arg * 4
    S = arg ** 2
    D = (2 ** (0.5)) * arg
    k = (P,S, format(D, ".5f"))
    return k

arg = int(input())
print(square(arg))