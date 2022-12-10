carrying = [0]

elf_num = 0
with open("input1+2.txt", "r") as file:
    while line := file.readline():
        if line == "\n":
            elf_num += 1
            carrying.append(0)
        else:
            carrying[elf_num] += int(line)

max_cals = [0, 0, 0]
for e in carrying:
    if e > min(max_cals):
        max_cals[0] = e
        max_cals = sorted(max_cals)

print(sum(max_cals))
