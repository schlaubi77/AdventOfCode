const fs = require('fs');
const readline = require('readline');

const file = readline.createInterface({
        input: fs.createReadStream('input.txt'),
        output: process.stdout,
        terminal: false
});

grid = [] // x and y are actually swaped => x vertical; y horizontal
index = 0
foundTrees = [] //x;y

file.on('line', (line) => {
    grid[index] = line
    index++
});

file.on('close', () => {
    highestScore = 0
    for(x = 0; x < grid[0].length; x++) {
        for(y = 0; y < grid.length; y++) {
            height = grid[x][y]

            //left
            left = 0
            for(checkY = y - 1; checkY >= 0; checkY--) {
                left++
                if(grid[x][checkY] >= height) {
                    break
                }
            }

            //right
            right = 0
            for(checkY = y + 1; checkY < grid[0].length; checkY++) {
                right++
                if(grid[x][checkY] >= height) {
                    break
                }
            }

            //top
            top = 0
            for(checkX = x - 1; checkX >= 0; checkX--) {
                top++
                if(grid[checkX][y] >= height) {
                    break
                }
            }

            //bottom
            bottom = 0
            for(checkX = x + 1; checkX < grid.length; checkX++) {
                bottom++
                if(grid[checkX][y] >= height) {
                    break
                }
            }
            score = top * bottom * left * right
            console.log(score)
            if(score > highestScore) {
                highestScore = score
            }
        }
    }
    console.log(highestScore)
});
