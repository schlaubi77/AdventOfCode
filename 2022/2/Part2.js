const fs = require('fs');
const readline = require('readline');

const file = readline.createInterface({
        input: fs.createReadStream('input.txt'),
        output: process.stdout,
        terminal: false
});

function getFromChar(c) {
    switch (c) {
        case "A":
        case "X":
            return 1
        case "B":
        case "Y":
            return 2
        case "C":
        case "Z":
            return 3
        default:
            throw new Error("Invalid char")
    }
}

function outcome(c) {
    switch (c) {
        case "X":
            return 0
        case "Y":
            return 3
        case "Z":
            return 6
    }
}

function myMove(result, elf) {
    switch (result) {
        case "X":
            switch (elf) {
                case 1:
                    return 3;
                case 2:
                    return 1;
                case 3:
                    return 2;
            }
        case "Y":
            return elf
        case "Z":
            switch (elf) {
                case 1:
                    return 2;
                case 2:
                    return 3;
                case 3:
                    return 1;
            }
    }
}

score = 0

file.on('line', (line) => {
        score += myMove(line[2], getFromChar(line[0])) + outcome(line[2])
});

file.on('close', () => {
    console.log(score)
})