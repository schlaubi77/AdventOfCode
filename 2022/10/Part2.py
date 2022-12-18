import numpy as np
import matplotlib.pyplot as plt
current_cycle = 0
value = 1

drawing_pos = 0
screen = np.zeros((6, 40))


def draw():
    global drawing_pos, value
    print(f"{drawing_pos} {value}")
    screen[drawing_pos // 40][drawing_pos % 40] = 1 if (value - 1) <= drawing_pos % 40 <= (value + 1) else 0
    drawing_pos += 1


with open("input.txt", "r") as file:
    while line := file.readline():
        draw()
        if line.startswith("addx"):
            draw()
            value += int(line.split(" ")[1])

plt.imshow(screen, cmap="gray")
plt.show()
