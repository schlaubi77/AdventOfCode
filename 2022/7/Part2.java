import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

public class Part2 {
	
	public static void main(String[] args) throws FileNotFoundException {
		Scanner scan = new Scanner(new File(System.getProperty("user.dir"), "input.txt"));
		
		Map<String, Integer> fileSizes = new HashMap<>();
		List<String> currentPath = new ArrayList<>();
		int totalUsedSpace = 0;
		
		while(scan.hasNextLine()) {
			String line = scan.nextLine();
			String[] parts = line.split(" ");
			
			if(parts[1].equals("cd")) {
				if(parts[2].equals("..")) {
					currentPath.remove(currentPath.size() - 1);
				} else if(parts[2].equals("/")) {
					currentPath.clear();
				} else {
					currentPath.add(parts[2]);
				}
				
			} else if(!parts[1].equals("ls")) {
				if(!parts[0].equals("dir")) {
					totalUsedSpace += Integer.parseInt(parts[0]);
					
					String addedPath = "";
					for(String s : currentPath) {
						addedPath += "/" + s;
						if(fileSizes.containsKey(addedPath)) {
							fileSizes.put(addedPath, fileSizes.get(addedPath) + Integer.parseInt(parts[0]));
						} else {
							fileSizes.put(addedPath, Integer.parseInt(parts[0]));
						}
						
					}
				}
			}
		}	
		int smallest = Integer.MAX_VALUE;
		for(int i : fileSizes.values()) {
			if(i < smallest && i > (totalUsedSpace - 40_000_000)) {
				smallest = i;
			}
		}
		System.out.println(smallest);
	}
}
