import java.io.File;
import java.io.FileNotFoundException;
import java.util.NoSuchElementException;
import java.util.Scanner;

public class Part2 {
	public static void main(String[] args) throws FileNotFoundException {
		Scanner scan = new Scanner(new File(System.getProperty("user.dir"), "input.txt"));
		int sum = 0;
		while(true) {
			try {
				String first = scan.nextLine();
				String second = scan.nextLine();
				String third = scan.nextLine();
				int priority = 0;
				for(char c : first.toCharArray()) {
					if(second.contains(String.valueOf(c)) && third.contains(String.valueOf(c))) {
						priority = getPriority(c);
						break;
					}
				}
				sum += priority;
			} catch(NoSuchElementException ex) {
				break;
			}
		}
		System.out.println(sum);
		
	}
	
	private static int getPriority(char c) {
		if(Character.isUpperCase(c)) {
			return Character.getNumericValue(c) - 9 + 26;
		} else {
			return Character.getNumericValue(c) - 9;
		}
	}
}