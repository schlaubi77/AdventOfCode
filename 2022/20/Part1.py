encrypted = []
actual_value = []

with open("input.txt", "r") as file:
    while line := file.readline():
        actual_value.append(int(line))
        encrypted.append(len(encrypted))


for item in range(len(encrypted)):
    move_by = actual_value[item]
    i = encrypted.index(item)

    encrypted.remove(item)
    new_pos = (i + move_by + len(encrypted)) % len(encrypted)

    encrypted.insert(new_pos, item)

grove = 0
for i in [1000, 2000, 3000]:
    grove += actual_value[encrypted[(encrypted.index(actual_value.index(0)) + i) % len(encrypted)]]

print(grove)
