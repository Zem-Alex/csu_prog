def season(arg):
    if arg <= 2 or arg == 12:
        return "Winter"
    if arg <= 5:
        return "Spring"
    if arg <= 8:
        return "Summer"
    if arg <= 11:
        return "Autumn"

arg = int(input())
print(season(arg))