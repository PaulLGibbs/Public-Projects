//going to be what the piece factory creates

public class Piece {
	
	
	private String title = "";

	private String boardDisplay = "";
	private boolean color = false; //false for black true for white 
	private boolean firstPawnMove = false;
	private int XPos = 0;
	private int YPos = 0;
	GameManager gm = GameManager.getInstance();
	
	public Piece(String title,  boolean color, int X, int Y) {
		this.title = title;
		this.color = color;
		XPos = X;
		YPos = Y;
		
		if(this.color) {//sets white displays
			switch(this.title) {
			case "King":
				boardDisplay = "K";
				break;
			case "Queen":
				boardDisplay = "Q";
				break;
			case "Rook":
				boardDisplay = "R";
				break;
			case "Bishop":
				boardDisplay = "B";
				break;
			case "Knight":
				boardDisplay = "k";
				break;
			case "Pawn": 
				boardDisplay = "p";
				firstPawnMove = true;
				break;
			}
		}else {//sets black displays
			switch(this.title) {
			case "King":
				boardDisplay = "K";
				break;
			case "Queen":
				boardDisplay = "Q";
				break;
			case "Rook":
				boardDisplay = "R";
				break;
			case "Bishop":
				boardDisplay = "B";
				break;
			case "Knight":
				boardDisplay = "k";
				break;
			case "Pawn": 
				boardDisplay = "p";
				firstPawnMove = true;
				break;
			}
		}
	}
	
	public int getX() {
		return XPos;
	}
	
	public int getY() {
		return YPos;
	}
	
	public void setPos(int x,int Y) {
		XPos = x;
		YPos = Y;
	}
	

	
	public void setBoardDisplay(String disp) {
		boardDisplay = disp;
	}
	
	public String getDisplay() {

		return boardDisplay;
	}
	
	public boolean getFirstPawnMove() {
		return firstPawnMove;
	}

}
