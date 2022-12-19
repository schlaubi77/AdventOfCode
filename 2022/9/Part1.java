import java.io.File;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.HashSet;
import java.util.Scanner;

public class Part1 {

	public static void main(String[] args) throws IOException {
		Scanner scan = new Scanner(new File(System.getProperty("user.dir"), "input.txt"), StandardCharsets.UTF_8);

		int[] posHead = { 0, 0 };
		int[] posTail = { 0, 0 };
		HashSet<String> list = new HashSet<>();

		list.add(encode(posTail));
		while (scan.hasNext()) {

			char action = scan.next().charAt(0);
			
			int iterations = scan.nextInt();
			
			int changeX = 0;
			int changeY = 0;
			switch (action) {
			case 'U':
				changeY = -1;
				break;
			case 'D':
				changeY = 1;
				break;
			case 'R':
				changeX = 1;
				break;
			case 'L':
				changeX = -1;
				break;
			}
			
			for(int i = 0; i < iterations; i++) {
				posHead[0] += changeX;
				posHead[1] += changeY;
				
				posTail = move(posTail, posHead);
				
                list.add(encode(posTail));
			}
		}
		System.out.println(list.size());
	}
	
	private static int[] move(int[] tail, int[] head) {
		if(Math.abs(tail[0] - head[0]) > 1) {
			tail[0] += (head[0] - tail[0]) / 2;
			if(head[1] != tail[1]) {
				tail[1] += (head[1] - tail[1]);
			}
		}
		
		if(Math.abs(tail[1] - head[1]) > 1) {
			tail[1] += (head[1] - tail[1]) / 2;
			if(head[0] != tail[0]) {
				tail[0] += (head[0] - tail[0]);
			}
		}
		return tail;
	}
	
	private static String encode(int[] pos) {
		return pos[0] + ";" + pos[1];
	}
}
