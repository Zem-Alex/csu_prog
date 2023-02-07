def arithmetic(arg1, arg2, arg3):
    if arg3 == "+":
        return arg1 + arg2
    if arg3 == "-":
        return arg1 - arg2
    if arg3 == "*":
        return arg1 * arg2
    if arg3 == "/":
        return arg1 / arg2
    return "Неизвестная операция"

arg1 = int(input())
arg2 = int(input())
arg3 = input()
print(arithmetic(arg1, arg2, arg3))