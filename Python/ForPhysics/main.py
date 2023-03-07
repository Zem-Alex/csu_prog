import math

"""IU = 0
T = 0

while True:
    IU = float(input("Enter IU: "))
    T = float(input("Enter T: "))
    print(IU / (0.9 * (T**4) * 0.0000185))"""


"""while True:
    IU = float(input("Enter IU: "))
    print( math.log(IU / 0.0000185))"""


"""while True:
    T = float(input("Enter T: "))

    print(str((0.00000302076 * (T**3.5))/(0.9 * (T**4))) + '\n')"""

"""for i in range(0,361):
    if (i % 15 == 0):
        print(i, math.cos(math.radians(i)) ** 2)"""

while True:
    d = float(input("Enter d: "))
    print(str((d/2)*7.5) + '\n')
    print(str(((d/2)*7.5)**2) + '\n')