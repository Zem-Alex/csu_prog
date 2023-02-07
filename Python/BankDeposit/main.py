def bank(a, years):
    while years > 0:
        a += a * 0.1
        years -= 1
    return a

a = int(input())
years = int(input())
print(bank(a, years))