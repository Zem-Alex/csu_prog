import os

hostname = "vk.com"


file1 = open('pingg.txt', 'r')
file2 = open('pingg2.txt', 'w')
while True:

    line = file1.readline()
    response = os.system("ping -n 1 " + line)
    if response == 0:
        file2.write(f"{line[:-1]} : is up!")
        file2.write(f"\n")

    else:
        file2.write(f"{line[:-1]} : is down!")
        break


file1.close