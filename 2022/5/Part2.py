from collections import deque

crates = [deque() for d in range(9)]  # bottom index 0

with open("input.txt", "r") as file:
    while (l := file.readline())[1] != "1":
        for i in range(9):
            if (letter := l[4 * i + 1]) != " ":
                crates[i].appendleft(letter)
    file.readline()
    print(crates)
    while l := file.readline():
        amount, fr, to = l.replace("move ", "").replace("from ", "").replace("to ", "").split(" ")
        amount, fr, to = [int(i) for i in [amount, fr, to]]
        move = deque()
        for i in range(amount):
            try:
                move.append(crates[fr - 1].pop())
            except IndexError:
                print("info")

        for i in range(len(move)):
            crates[to - 1].append(move.pop())

    result = ""
    for tower in crates:
        result += tower[-1]
    print(result)