# Заданный IP-адрес и маска
ip_address = "10.42.140.222"
subnet_mask = "255.255.0.0"

# Разделение на октеты
ip_octets = [int(octet) for octet in ip_address.split(".")]
mask_octets = [int(octet) for octet in subnet_mask.split(".")]

network_address_octets = [ip_octets[i] & mask_octets[i] for i in range(4)]

network_address = ".".join(map(str, network_address_octets))

print("Адрес сети:", network_address)

# Заданный адрес сети и маска
ip_address = "10.42.140.222"
network_mask = "10.42.0.0"

# Разделение на октеты
subnet_octets = [int(octet) for octet in ip_address.split(".")]
network_octets = [int(octet) for octet in network_mask.split(".")]

network_address_octets = [subnet_octets[i] - network_octets[i] for i in range(4)]

network_address = ".".join(map(str, network_address_octets))

print("Адрес хоста:", network_address)


