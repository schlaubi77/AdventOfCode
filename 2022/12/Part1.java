import java.io.File;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class Part1 {

	public static void main(String[] args) throws IOException {
		Scanner scan = new Scanner(new File(System.getProperty("user.dir"), "input.txt"), StandardCharsets.UTF_8);

		int[][] heightLevels = new int[41][];

		int[] entryNode = new int[2];
		int[] exitNode = new int[2];

		int index = 0;
		while (scan.hasNextLine()) {
			String line = scan.nextLine();
			int[] row = new int[line.length()];
			for (char c : line.toCharArray()) {
				row[index % line.length()] = Character.getNumericValue(c) - 10;
				if (c == 'S') {
					row[index % line.length()] = 0;
					entryNode[0] = index / line.length();
					entryNode[1] = index % line.length();

				} else if (c == 'E') {
					row[index % line.length()] = 25;
					exitNode[0] = index / line.length();
					exitNode[1] = index % line.length();
				}
				index++;
			}
			heightLevels[(index / line.length()) - 1] = row;
		}

		int[][] actions = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };

		// BFS (Breadth First Search)
		Queue<int[]> queue = new LinkedList<>();

		int[][][] parentNode = new int[41][][];
		boolean[][] visited = new boolean[41][];

		for (int i = 0; i < parentNode.length; i++) {
			parentNode[i] = new int[heightLevels[0].length][];
			visited[i] = new boolean[heightLevels[0].length];
		}

		queue.add(entryNode);
		visited[entryNode[0]][entryNode[1]] = true;
		
		while (!queue.isEmpty()) {
			int[] node = queue.poll();
			
			
			for(int[] action : actions) {
				int[] neighbour = new int[2];
				neighbour[0] = Math.min(Math.max(node[0] + action[0], 0), heightLevels.length - 1);
				neighbour[1] = Math.min(Math.max(node[1] + action[1], 0), heightLevels[0].length - 1);
				if(!visited[neighbour[0]][neighbour[1]]) {
					if(heightLevels[neighbour[0]][neighbour[1]] <= heightLevels[node[0]][node[1]] + 1) {
						queue.add(neighbour);
						parentNode[neighbour[0]][neighbour[1]] = node;
						visited[neighbour[0]][neighbour[1]] = true;
					}
				}
			}
		}
		
		int pathLength = 0;
		int[] currentNode = exitNode;
		
		while(!currentNode.equals(entryNode)) {
			currentNode = parentNode[currentNode[0]][currentNode[1]];
			pathLength++;
		}
		System.out.println(pathLength);
		
	}
}
