import java.io.File;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Scanner;

public class Part2 {

	public static void main(String[] args) throws IOException {
		Scanner scan = new Scanner(new File(System.getProperty("user.dir"), "input.txt"), StandardCharsets.UTF_8);

		int[][] heightLevels = new int[41][];

		int[] exitNode = new int[2];
		
		List<int[]> lowestHeightSpots = new ArrayList<>();
		
		int index = 0;
		while (scan.hasNextLine()) {
			String line = scan.nextLine();
			int[] row = new int[line.length()];
			for (char c : line.toCharArray()) {
				row[index % line.length()] = Character.getNumericValue(c) - 10;
				if (c == 'S') {
					row[index % line.length()] = 0;
				} else if (c == 'E') {
					row[index % line.length()] = 25;
					exitNode[0] = index / line.length();
					exitNode[1] = index % line.length();
				} else if(c == 'a') {
					int[] pos = new int[2];
					pos[0] = index / line.length();
					pos[1] = index % line.length();
					lowestHeightSpots.add(pos);
				}
				index++;
			}
			heightLevels[(index / line.length()) - 1] = row;
		}

		int[][] actions = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };
		
		List<Integer> distances = new ArrayList<>();
		
		// BFS (Breadth First Search)
		for(int[] startingNode : lowestHeightSpots) {
			Queue<int[]> queue = new LinkedList<>();
	
			int[][][] parentNode = new int[41][][];
			boolean[][] visited = new boolean[41][];
	
			for (int i = 0; i < parentNode.length; i++) {
				parentNode[i] = new int[heightLevels[0].length][];
				visited[i] = new boolean[heightLevels[0].length];
			}
	
			queue.add(startingNode);
			visited[startingNode[0]][startingNode[1]] = true;
			
			
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
			while(!startingNode.equals(currentNode)) {
				// do not evaluate the route if the end was not reached. For example 0|5 in my input
				if(currentNode == null) {
					pathLength = Integer.MAX_VALUE;
					break;
				}
				currentNode = parentNode[currentNode[0]][currentNode[1]];
				pathLength++;
			}
			distances.add(pathLength);

		}
		
		int leastSteps = Integer.MAX_VALUE;
		for(int s : distances) {
			if(s < leastSteps) {
				leastSteps = s;
			}
		}
		System.out.println(leastSteps);
		
	}
}
