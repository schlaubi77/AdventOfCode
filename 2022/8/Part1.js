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
    // checking left
    for(x = 0; x < grid[0].length; x++) {
        highestTree = -1
        for(y = 0; y < grid.length; y++) {
            if(grid[x][y] > highestTree) {
                highestTree = grid[x][y]
                if(!foundTrees.includes(x + ";" + y)) {
                    foundTrees.push(x + ";" + y)
                }
            }
        }
    }
    
    // checking right
    for(x = 0; x < grid[0].length; x++) {
        highestTree = -1
        for(y = (grid.length - 1); y >= 0; y--) {
            if(grid[x][y] > highestTree) {
                highestTree = grid[x][y]
                if(!foundTrees.includes(x + ";" + y)) {
                    foundTrees.push(x + ";" + y)
                }
            }
        }
    }
    
   // checking top
    for(y = 0; y < grid.length; y++) {
        highestTree = -1
        for(x = 0; x < grid[0].length; x++) {
            if(grid[x][y] > highestTree) {
                highestTree = grid[x][y]
                if(!foundTrees.includes(x + ";" + y)) {
                    foundTrees.push(x + ";" + y)
                }
            }
       }
   }
   
   // checking bottom
    for(y = 0; y < grid.length; y++) {
        highestTree = -1
        for(x = (grid[0].length - 1); x >= 0; x--) {
            if(grid[x][y] > highestTree) {
                highestTree = grid[x][y]
                if(!foundTrees.includes(x + ";" + y)) {
                    foundTrees.push(x + ";" + y)
                }
            }
        }
    }
    console.log(foundTrees.length)
})