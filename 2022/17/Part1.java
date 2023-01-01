import javax.sound.midi.Sequence;
import java.io.File;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.Scanner;

/*
I already tried the same code in c++ but it didn't work there.
then I basically copied it into java, and now it works; weird
 */
public class Part1 {

    public static void main(String[] args) throws IOException {
        String sequence = new Scanner(new File(System.getProperty("user.dir"), "input.txt"), StandardCharsets.UTF_8).nextLine();

        boolean[][] board = new boolean[7][10000];

        int highestRock = 0;
        int currentRockType = 0; // 0: horizontal, 1: +, 2: inverted L, 3: vertical, 4: 2x2

        final int segmentsOfRocks[][][] = {
            {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {0, 0}},
            {{0, 1}, {1, 2}, {1, 1}, {1, 0}, {2, 1}},
            {{0, 0}, {1, 0}, {2, 0}, {2, 1}, {2, 2}},
            {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 0}},
            {{0, 0}, {0, 1}, {1, 0}, {1, 1}, {0, 0}}
        };

        int[] position = {2, highestRock + 3}; // position bottom left
        int placedRocks = 0;

        int index = 0;

        while (placedRocks < 2022) {

            char jet = sequence.charAt(index);
            index = (index + 1) % sequence.length();

            // try sidewards move
            if(jet == '<') {
                boolean canMove = true;
                for(int i = 0; i < 5; i++){
                    int newPos0 = position[0] - 1 + segmentsOfRocks[currentRockType][i][0];
                    if(!(newPos0 >= 0 && newPos0 <= 6)){
                        canMove = false;
                        break;
                    }
                    if(board[newPos0][position[1] + segmentsOfRocks[currentRockType][i][1]]) {
                        canMove = false;
                        break;
                    }
                }
                if(canMove){
                    position[0]--;
                }
            } else {
                boolean canMove = true;
                for(int i = 0; i < 5; i++){
                    int newPos0 = position[0] + 1 + segmentsOfRocks[currentRockType][i][0];
                    if(!(newPos0 >= 0 && newPos0 <= 6)){
                        canMove = false;
                        break;
                    }
                    if(board[newPos0][position[1] + segmentsOfRocks[currentRockType][i][1]]) {
                        canMove = false;
                        break;
                    }
                }
                if(canMove){
                    position[0]++;
                }
            }

            // try downwards move
            boolean canFall = true;
            for(int i = 0; i < 5; i++) {
                int newPos1 = position[1] - 1 + segmentsOfRocks[currentRockType][i][1];
                if(newPos1 < 0) {
                    canFall = false;
                    break;
                }
                if(board[position[0] + segmentsOfRocks[currentRockType][i][0]][newPos1]) {
                    canFall = false;
                    break;
                }
            }

            if(canFall){
                position[1]--;
            } else{
                // place rock
                for(int i = 0; i < 5; i++) {
                    board[position[0] + segmentsOfRocks[currentRockType][i][0]][position[1] + segmentsOfRocks[currentRockType][i][1]] = true;
                    if(position[1] + segmentsOfRocks[currentRockType][i][1] > highestRock) {
                        highestRock = position[1] + segmentsOfRocks[currentRockType][i][1];
                    }
                }
                // next rock
                placedRocks++;
                position[0] = 2;
                position[1] = highestRock + 4;
                currentRockType = placedRocks % 5;
            }
        }
        System.out.println(highestRock + 1);
    }
}
