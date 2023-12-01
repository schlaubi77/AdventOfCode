#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int height = 200;
const int width = 150;

int grid[height][width]; // 0: empty, 1: open, 2: wall

string instructions;

int x = 0, y = 0;

int heading = 0; // 0: right, 1: down, 2: left, 3: up

void moveHeading(int steps) {
    int tempX = x;
    int tempY = y;
    for (int i = 0; i < steps; i++) {
        switch(heading) {
        case 0:
            tempX++;
            tempX %= width;
            break;
        case 1:
            tempY++;
            tempY %= height;
            break;
        case 2:
            tempX--;
            if (tempX < 0) {
                tempX = width - 1;
            }
            break;
        case 3:
            tempY--;
            if (tempY < 0) {
                tempY = height - 1;
            }
            break;
        }

        switch (grid[tempY][tempX]) {
        case 0:
            steps++;
            break;
        case 1:
            x = tempX;
            y = tempY;
            break;
        case 2:
            return;
        }
    }
}


int main()
{
    ifstream file("input.txt");
    string line;


    for (int i = 0; i < height; i++) {
        getline(file, line);
        int j = 0;
        for (char c : line) {
            switch (c) {
            case '.':
                grid[i][j] = 1;
                break;
            case '#':
                grid[i][j] = 2;
            }
            j++;
        }
    }
    getline(file, line);
    getline(file, line);
    instructions = line;

    // find start pos by moving right to the first filled spot
    moveHeading(1);

    int stepSize = 0;

    for (char c : instructions) {
        if (isdigit(c)) {
            stepSize = stepSize * 10 + c - '0';
        }
        else {
            moveHeading(stepSize);
            stepSize = 0;
            if (c == 'R') {
                heading++;
            }
            else if(c == 'L') {
                heading--;
            }
            heading %= 4;
            if (heading < 0) {
                heading = 3;
            }
        }
    }

    moveHeading(stepSize);

    cout << "x:" << x << "; y:" << y << "; heading:" << heading << endl;
    cout << "password:" << 1000 * (y + 1) + 4 * (x + 1) + heading;

    return 0;
}