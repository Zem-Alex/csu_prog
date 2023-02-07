def is_prime(arg):
    for i in range(2,arg - 1):
        if arg % i == 0:
            return "False"
    return "True"

arg = int(input())
print(is_prime(arg))