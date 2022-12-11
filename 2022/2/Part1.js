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

function outcome(me, elf) {
    switch (me) {
        case 1:
            switch (elf) {
                case 1:
                    return 3;
                case 2:
                    return 0;
                case 3:
                    return 6;
            }
        case 2:
            switch (elf) {
                case 1:
                    return 6;
                case 2:
                    return 3;
                case 3:
                    return 0;
            }
        case 3:
            switch (elf) {
                case 1:
                    return 0;
                case 2:
                    return 6;
                case 3:
                    return 3;
            }
    }
}

score = 0

file.on('line', (line) => {
        score += getFromChar(line[2]) + outcome(getFromChar(line[2]), getFromChar(line[0]))
});

file.on('close', () => {
    console.log(score)
})