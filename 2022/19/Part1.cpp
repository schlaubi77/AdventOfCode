#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

#define INPUT_LENGTH 30

using namespace std;

struct Blueprint {
    unsigned short oreCostOre;
    unsigned short oreCostClay;
    unsigned short oreCostObsidian;
    unsigned short clayCostObsidian;
    unsigned short oreCostGeode;
    unsigned short obsidianCostGeode;
};

struct State {
    int timePassed = 0;
    int ore = 0;
    int oreRobots = 0;
    int clay = 0;
    int clayRobots = 0;
    int obsidian = 0;
    int obsidianRobots = 0;
    int geode = 0;
    int geodeRobots = 0;
};

Blueprint createBlueprint(string s) {
    int i = 0;
    int spaces[31];
    int index = 0;
    while (i < s.size() - 9) {
        spaces[index] = s.find(" ", i);
        i = spaces[index] + 1;
        index++;
    }
    Blueprint bp;
    bp.oreCostOre = stoi(s.substr(spaces[5] + 1, spaces[6] - spaces[5] - 1));
    bp.oreCostClay = stoi(s.substr(spaces[11] + 1, spaces[12] - spaces[11] - 1));
    bp.oreCostObsidian = stoi(s.substr(spaces[17] + 1, spaces[18] - spaces[17] - 1));
    bp.clayCostObsidian = stoi(s.substr(spaces[20] + 1, spaces[21] - spaces[20] - 1));
    bp.oreCostGeode = stoi(s.substr(spaces[26] + 1, spaces[27] - spaces[26] - 1));
    bp.obsidianCostGeode = stoi(s.substr(spaces[29] + 1, spaces[30] - spaces[29] - 1));
    
    return bp;
}


int maxOnThisBlueprint = 0;

int getBestGeodes(Blueprint bp, State state) {
    int maxPossible = state.geode;
    int currentEarn = state.geodeRobots;
    for (int i = state.timePassed; i < 24; i++) {
        maxPossible += currentEarn++;
    }

    if (maxPossible <= maxOnThisBlueprint) {
        return maxOnThisBlueprint;
    }

    if (state.timePassed >= 24) {
        return maxOnThisBlueprint = max(maxOnThisBlueprint, state.geode);
    }

    int r = 0;

    if (state.ore >= bp.oreCostGeode && state.obsidian >= bp.obsidianCostGeode) {
        State copy = state;

        copy.timePassed++;
        copy.ore += copy.oreRobots;
        copy.clay += copy.clayRobots;
        copy.obsidian += copy.obsidianRobots;
        copy.geode += copy.geodeRobots;

        copy.geodeRobots++;
        copy.ore -= bp.oreCostGeode;
        copy.obsidian -= bp.obsidianCostGeode;

        r = max(r, getBestGeodes(bp, copy));

        if (state.oreRobots >= bp.oreCostGeode && state.obsidianRobots >= bp.obsidianCostGeode) {
            return r;
        }
    }

    if (state.ore >= bp.oreCostObsidian && state.clay >= bp.clayCostObsidian && state.obsidianRobots < bp.obsidianCostGeode) {
        State copy = state;

        copy.timePassed++;
        copy.ore += copy.oreRobots;
        copy.clay += copy.clayRobots;
        copy.obsidian += copy.obsidianRobots;
        copy.geode += copy.geodeRobots;

        copy.obsidianRobots++;
        copy.ore -= bp.oreCostObsidian;
        copy.clay -= bp.clayCostObsidian;

        r = max(r, getBestGeodes(bp, copy));
    }

    if (state.ore >= bp.oreCostClay && state.clayRobots < bp.clayCostObsidian) {
        State copy = state;

        copy.timePassed++;
        copy.ore += copy.oreRobots;
        copy.clay += copy.clayRobots;
        copy.obsidian += copy.obsidianRobots;
        copy.geode += copy.geodeRobots;

        copy.clayRobots++;
        copy.ore -= bp.oreCostClay;

        r = max(r, getBestGeodes(bp, copy));
    }

    if (state.ore >= bp.oreCostOre && state.oreRobots < max(bp.oreCostClay, max(bp.oreCostGeode, bp.oreCostObsidian))) {
        State copy = state;

        copy.timePassed++;
        copy.ore += copy.oreRobots;
        copy.clay += copy.clayRobots;
        copy.obsidian += copy.obsidianRobots;
        copy.geode += copy.geodeRobots;

        copy.oreRobots++;
        copy.ore -= bp.oreCostOre;

        r = max(r, getBestGeodes(bp, copy));
    }

    State copy = state;

    copy.timePassed++;
    copy.ore += copy.oreRobots;
    copy.clay += copy.clayRobots;
    copy.obsidian += copy.obsidianRobots;
    copy.geode += copy.geodeRobots;

    r = max(r, getBestGeodes(bp, copy));

    return r;
}

int main()
{
    auto start = chrono::system_clock::now();
    ifstream file("input.txt");
    Blueprint blueprints[INPUT_LENGTH];
    string line;

    int index = 0;

    while (getline(file, line)) {
        blueprints[index] = createBlueprint(line);
        index++;
    }

    int result = 0;
    
    for (int i = 0; i < INPUT_LENGTH; i++) {
        maxOnThisBlueprint = 0;

        State baseState;
        baseState.oreRobots = 1;

        result += getBestGeodes(blueprints[i], baseState) * (i + 1);
    }

    cout << result << endl;

    chrono::duration<double> elapsed_seconds = chrono::system_clock::now() - start;

    cout << "Time taken: " << elapsed_seconds.count() << "s" << endl;
    
    return 0;
}