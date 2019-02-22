//this is the view of mvc
public class View {
	GameManager gm = GameManager.getInstance();
	private Piece[][] board = gm.passBoard();
	public void display() {
		board = gm.passBoard();
		System.out.println("  0 1 2 3 4 5 6 7 ");
		for(int i = 0; i<8;i++) {
			System.out.print(i+" ");
			for(int j = 0; j<8;j++) {
				System.out.print(board[j][i].getDisplay() + " ");
			}
			
			System.out.println();;
		}
		if((gm.getTurn() % 2) == 0) {
			System.out.print("White(Top) turn\n");
		}else {
			System.out.print("Black(Bottom) turn\n");
		}

	}
}
