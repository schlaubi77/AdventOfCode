from collections import deque

valves = {}
flow_rates = {}
start = "AA"
with open("input.txt", "r") as file:
    index = 0
    while line := file.readline():
        args = line.split(" ")
        valves[args[1]] = [x.replace(",", "").replace("\n", "") for x in args[9:]]
        flow_rates[args[1]] = int(args[4].replace("rate=", "").replace(";", ""))
        index += 1

shortest_connections = {}


# breath first search
def bfs_path_length(start_node, end_node):
    queue = deque()
    queue.append([start_node, 0])

    while node := queue.popleft():
        for child in valves[node[0]]:
            if child == end_node:
                return node[1] + 1
            else:
                queue.append([child, node[1] + 1])


non_zero_valves = []

for v in valves.keys():
    if v == start or flow_rates[v] != 0:
        if v != start:
            non_zero_valves.append(v)
        shortest_connections[v] = {}
        for v2 in valves.keys():
            if flow_rates[v2] != 0:
                shortest_connections[v][v2] = bfs_path_length(v, v2)

valves_to_bitmap = {}

for i, e in enumerate(non_zero_valves):
    valves_to_bitmap[e] = i

cache = {}


def dfs_optimal_score(position, time, opened):  # opened valves as bit mask
    if (position, time, opened) in cache:
        return cache[(position, time, opened)]
    max_score = 0
    for neighbour in shortest_connections[position]:
        bitmask = 1 << valves_to_bitmap[neighbour]
        if bitmask & opened:
            continue
        remaining_time = time - shortest_connections[position][neighbour] - 1
        if remaining_time <= 1:
            continue
        max_score = max(max_score, dfs_optimal_score(neighbour, remaining_time, bitmask | opened) + remaining_time * flow_rates[neighbour])

    cache[(position, time, opened)] = max_score
    return max_score


max_team_score = 0
filled_bitmask = (1 << len(non_zero_valves)) - 1

for i in range(filled_bitmask // 2):
    max_team_score = max(max_team_score, dfs_optimal_score(start, 26, i) + dfs_optimal_score(start, 26, filled_bitmask ^ i))

print(max_team_score)
