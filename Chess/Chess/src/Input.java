import java.util.Scanner;
//this is the controller for input
public class Input {
	Scanner reader = new Scanner(System.in);
	
	public int getPositionX() {
		System.out.print("Choose X value of piece you want to move: ");
		int inputX = reader.nextInt();
		return inputX;
	}	
	public int getPositionY() {
		System.out.print("\nChoose Y value of piece you want to move: ");
		int inputY = reader.nextInt();
		return inputY;
	}
		
	public int setPositionX() {
		System.out.print("Choose X value of where you want to move to: ");
		int inputX = reader.nextInt();
		return inputX;
	}	
	public int setPositionY() {
		System.out.print("\nChoose Y value of where you want to move to: ");
		int inputY = reader.nextInt();
		return inputY;
	}
}
