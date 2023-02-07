def XOR_cipher1(data, key):
    mass = []
    for d in data:
        value = ord(d)
        for k in key:
            value ^= ord(k)
        mass.append(chr(value))
    return "".join(mass)

def XOR_cipher2(data: str, key: str) -> str:
    answer = []
    p = 0
    for d in data:
        answer.append(chr(ord(d)^ord(key[p])))
        p = (p+1)%len(key)
    return "".join(answer)

data = "test"
key = "1"
a1 = XOR_cipher1(data, key)
a2 = XOR_cipher1(a1, key)
b1 = XOR_cipher1(data, key)
b2 = XOR_cipher1(a1, key)

print(a1)
print(a2)
print(b1)
print(b2)
