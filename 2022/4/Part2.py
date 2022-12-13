with open("input.txt", "r") as file:
    count = 0
    while line := file.readline():
        first, second = line.split(",")
        begin1, end1 = first.split("-")
        begin2, end2 = second.split("-")
        begin1, begin2, end1, end2 = [int(i) for i in [begin1, begin2, end1, end2]]
        if not(end1 < begin2 or begin1 > end2):
            count += 1
    print(count)
