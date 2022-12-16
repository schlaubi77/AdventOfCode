import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

public class Part1 {
	
	public static void main(String[] args) throws FileNotFoundException {
		Scanner scan = new Scanner(new File(System.getProperty("user.dir"), "input.txt"));
		
		Map<String, Integer> fileSizes = new HashMap<>();
		List<String> currentPath = new ArrayList<>();
		
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
		int count = 0;
		for(int i : fileSizes.values()) {
			if(i <= 100000) {
				count += i;
			}
		}
		System.out.println(count);
	}
}
