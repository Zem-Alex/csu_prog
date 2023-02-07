def is_year_leap(arg):
    if arg % 4 == 0:
        return 1
    else:
        return 0

def date(day, month, year):
    if 1 <= month <= 12:
            if month == 1 and day == 31:
                return "true"
            if month == 2 and day == 29 and is_year_leap(year) == 1:
                return "true"
            if month == 2 and day == 28 and is_year_leap(year) == 0:
                return "true"
            if month == 3 and day == 31:
                return "true"
            if month == 4 and day == 30:
                return "true"
            if month == 5 and day == 31:
                return "true"
            if month == 6 and day == 30:
                return "true"
            if month == 7 and day == 31:
                return "true"
            if month == 8 and day == 31:
                return "true"
            if month == 9 and day == 30:
                return "true"
            if month == 10 and day == 31:
                return "true"
            if month == 11 and day == 30:
                return "true"
            if month == 12 and day == 31:
                return "true"
            else:
                return "false"
я
day = int(input())
month = int(input())
year = int(input())

print(date(day, month, year))