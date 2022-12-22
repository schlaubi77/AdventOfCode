import json


def compare(ob1, ob2): # 1: right order 2: wrong 0: next object
    if type(ob1) == int and type(ob2) == int:
        if ob1 == ob2:
            return 0
        if ob1 < ob2:
            return 1
        else:
            return 2

    elif type(ob1) == list and type(ob2) == list:
        for ind in range(max(len(ob1), len(ob2)) + 1):
            if ind >= len(ob1) == len(ob2):
                return 0
            elif ind >= len(ob1):
                return 1
            elif ind >= len(ob2):
                return 2
            else:
                com = compare(ob1[ind], ob2[ind])
                if com != 0:
                    return com

    else:
        if type(ob1) == int:
            return compare([ob1], ob2)
        else:
            return compare(ob1, [ob2])


sum_indices = 0
index = 0
with open("input.txt", "r") as file:
    while line1 := file.readline():
        index += 1
        line2 = file.readline()
        file.readline()

        loaded1 = json.loads('{"1":' + line1 + "}")["1"]
        loaded2 = json.loads('{"2":' + line2 + "}")["2"]

        i = 0
        res = 0
        while res == 0:
            if i >= len(loaded1):
                res = 1
            elif i >= len(loaded2):
                res = 2
            else:
                res = compare(loaded1[i], loaded2[i])

            i += 1

        if res == 1:
            sum_indices += index

    print(sum_indices)
