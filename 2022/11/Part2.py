items = []
static_args = []  # +/-, value
test = []  # int check, true, false
times_inspected = [0 for i in range(8)]

with open("input.txt", "r") as file:
    index = 0
    while line := file.readline():
        if line == "\n":
            index += 1
        elif line.startswith("Monkey"):
            items.append([int(x) for x in file.readline().replace(",", "").split(" ")[4:]])
            action = file.readline().split(" ")[2:]
            static_args.append([action[-2], action[-1]])
            test.append([int(file.readline().split(" ")[-1]), int(file.readline().split(" ")[-1]), int(file.readline().split(" ")[-1])])

factor = 1
for x in test:
    factor *= x[0]

for r in range(10000):
    for i in range(8):
        to_handle = items[i]
        items[i] = []
        for item in to_handle:
            if static_args[i][0] == "+":
                worry_level = item + int(static_args[i][1])
            elif static_args[i][1] != "old\n":
                worry_level = item * int(static_args[i][1])
            else:
                worry_level = item ** 2

            worry_level %= factor

            times_inspected[i] += 1
            if worry_level % test[i][0] == 0:
                items[test[i][1]].append(worry_level)
            else:
                items[test[i][2]].append(worry_level)

highest = [0, 0]
for e in times_inspected:
    if min(highest) < e:
        highest[0] = e
        highest = sorted(highest)

print(times_inspected)
print(highest[0] * highest[1])
