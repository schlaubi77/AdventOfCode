current_cycle = 0
value = 1

signal = 0


def check_cycle():
    global signal
    if current_cycle % 40 == 20:
        signal += current_cycle * value


with open("input.txt", "r") as file:
    while line := file.readline():
        current_cycle += 1
        check_cycle()
        if line.startswith("addx"):
            current_cycle += 1
            check_cycle()
            value += int(line.split(" ")[1])

print(signal)
