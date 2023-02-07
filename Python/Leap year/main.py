def is_year_leap(arg):
    if arg % 4 == 0:
        return "True"
    else:
        return "False"

arg = int(input())
print(is_year_leap(arg))