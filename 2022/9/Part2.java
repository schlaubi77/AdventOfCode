import java.io.File;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.HashSet;
import java.util.Scanner;

public class Part2 {

	public static void main(String[] args) throws IOException {
		Scanner scan = new Scanner(new File(System.getProperty("user.dir"), "input.txt"), StandardCharsets.UTF_8);

		int[][] positions = {
				{ 0, 0 },
				{ 0, 0 },
				{ 0, 0 },
				{ 0, 0 },
				{ 0, 0 },
				{ 0, 0 },
				{ 0, 0 },
				{ 0, 0 },
				{ 0, 0 },
				{ 0, 0 }
		};
		HashSet<String> list = new HashSet<>();

		list.add(encode(positions[9]));
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
				positions[0][0] += changeX;
				positions[0][1] += changeY;
				
				for(int i2 = 1; i2 < positions.length; i2++) {
					positions[i2] = move(positions[i2], positions[i2 - 1]);
				}
                list.add(encode(positions[9]));
			}
		}
		System.out.println(list.size());
	}
	
	private static int[] move(int[] tail, int[] head) {
		if(Math.abs(tail[0] - head[0]) > 1) {
			tail[0] += (head[0] - tail[0]) / 2;
			if(head[1] != tail[1]) {
				tail[1] += (head[1] - tail[1]) / Math.abs(head[1] - tail[1]);
			}
		}
		
		if(Math.abs(tail[1] - head[1]) > 1) {
			tail[1] += (head[1] - tail[1]) / 2;
			if(head[0] != tail[0]) {

				tail[0] += head[0] - tail[0] / Math.abs(head[0] - tail[0]);
			}
		}
		return tail;
	}
	
	private static String encode(int[] pos) {
		return pos[0] + ";" + pos[1];
	}
}
