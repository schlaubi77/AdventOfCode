import javax.sound.midi.Sequence;
import java.io.File;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Part2 {

    private static final int PLACED_ROCKS_OFFSET = 1010; // must be a multiple of 5
    public static void main(String[] args) throws IOException {
        String sequence = new Scanner(new File(System.getProperty("user.dir"), "input.txt"), StandardCharsets.UTF_8).nextLine();

        boolean[][] board = new boolean[7][30_000];

        int highestRock = 0;
        int currentRockType = 0; // 0: horizontal, 1: +, 2: inverted L, 3: vertical, 4: 2x2

        int indexToCheckRecursion = -1;
        int heightOffset = -1;
        List<Integer> heightsOnRecursion = new ArrayList<>();
        List<Integer> rockNumberOnRecursion = new ArrayList<>();


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

        while (placedRocks < 10_000) {

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

                if(currentRockType == 0) {

                    if(placedRocks == 1010 && indexToCheckRecursion == -1) {
                        heightOffset = highestRock;
                        indexToCheckRecursion = index;
                    }
                    if(index == indexToCheckRecursion) {
                        heightsOnRecursion.add(highestRock);
                        rockNumberOnRecursion.add(placedRocks);
                    }

                }

                // next rock
                placedRocks++;
                position[0] = 2;
                position[1] = highestRock + 4;
                currentRockType = placedRocks % 5;
            }
        }
        int heightStep = heightsOnRecursion.get(1) - heightsOnRecursion.get(0);
        int rockNumberStep = rockNumberOnRecursion.get(1) - rockNumberOnRecursion.get(0);

        for(int i = 1; i < heightsOnRecursion.size(); i++) {
            if(heightsOnRecursion.get(i) - heightsOnRecursion.get(i - 1) != heightStep) {
                System.out.println("Error");
            }
        }
        for(int i = 1; i < rockNumberOnRecursion.size(); i++) {
            if(rockNumberOnRecursion.get(i) - rockNumberOnRecursion.get(i - 1) != rockNumberStep) {
                System.out.println("Error2");
            }
        }
        System.out.printf("After a height of %d was reached with %d rocks dropped, the height increased by %d every %d rocks\n", heightStep, PLACED_ROCKS_OFFSET, heightStep, rockNumberStep);

        // I choose the number on line 106 so this works out
        if(1000000000000l % rockNumberStep == PLACED_ROCKS_OFFSET) {
            System.out.printf("After 1000000000000 rocks the tower is %d units tall\n", 1000000000000l / rockNumberStep * heightStep + heightOffset);
        } else {
            System.out.println("Set PLACED_ROCKS_OFFSET to " + (1000000000000l % rockNumberStep));
        }
    }
}
