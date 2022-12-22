import json


def compare(ob1, ob2):  # 1: right order 2: wrong 0: next object
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


def fully_compare(o1, o2):  # true: o1 "smaller" than o2
    res = 0
    i = 0
    while res == 0:
        if i >= len(o1):
            res = 1
        elif i >= len(o2):
            res = 2
        else:
            res = compare(o1[i], o2[i])
        i += 1

    if res == 1:
        return True
    elif res == 2:
        return False
    else:
        print("ERROR")


packets = [[[2]], [[6]]]
with open("input.txt", "r") as file:
    while line := file.readline():
        if line != "\n":
            packets.append(json.loads('{"1":' + line + "}")["1"])

for e in range(1, len(packets)):
    f = e
    while f > 0 and fully_compare(packets[f], packets[f - 1]):
        temp = packets[f]
        packets[f] = packets[f - 1]
        packets[f - 1] = temp
        f -= 1

decoder_key = 1
index = 1
for p in packets:
    if p == [[2]] or p == [[6]]:
        decoder_key *= index
    index += 1

print(decoder_key)
