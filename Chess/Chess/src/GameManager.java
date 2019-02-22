//singleton gamemanager represents the model

/* Board Example
 * white
 *  0 1 2 3 4 5 6 7
 *0 ♖  ♘  ♗   ♕  ♔   ♗  ♘   ♖
 *1 ♙  ♙  ♙   ♙  ♙   ♙  ♙   ♙
 *2 x x x x x x x x
 *3 x x x x x x x x
 *4 x x x x x x x x
 *5 x x x x x x x x
 *6 ♟  ♟  ♟   ♟  ♟  ♟   ♟   ♟
 *7 ♜  ♞  ♝   ♛  ♚  ♝   ♞   ♜
 * black
 * P = pawn R = rook K= Knight B = Bishop Q = Queen K= King
 * 
 *                      "\u2654 " + // white king
                        "\u2655 " + // white queen
                        "\u2656 " + // white rook
                        "\u2657 " + // white bishop
                        "\u2658 " + // white knight
                        "\u2659 " + // white pawn
                        "\n" +
                        "\u265A " + // black king
                        "\u265B " + // black queen
                        "\u265C " + // black rook
                        "\u265D " + // black bishop
                        "\u265E " + // black knight
                        "\u265F " + // black pawn
                        
             ♙ 	♙ 	♙ 	♙ 	♙ 	♙ 	♙ 	♙
	♖ 	♘ 	♗ 	♕ 	♔ 	♗ 	♘ 	♖
 */



class GameManager {
	private static GameManager gameManager = null;
	private Piece[][] board = new Piece[8][8];
	private Input in = new Input();
	private int turn = 0;

	//creates the singleton instance of gm
	public static GameManager getInstance(){
		if(gameManager == null){
			gameManager = new GameManager();
		}
		return gameManager;
	}
	
	public void play() {//todo
		int fromX = 0 , fromY = 0 , toX = 0 , toY = 0;
		PieceFactory factory = new PieceFactory();
		View view = new View();
		fillBoard();
		//view.display();
		factory.createBoard();
		while(stillTwoKings()) {
			view.display();
			fromX = in.getPositionX();
			fromY = in.getPositionY();
			toX = in.setPositionX();
			toY = in.setPositionY();
			//System.out.println(moveIsValid(fromX,fromY,toX,toY));
			if(moveIsValid(fromX,fromY,toX,toY)) {
				//board[fromX][fromY].setPos(toX,toY);
				Piece tempPiece = board[toX][toY];
				board[toX][toY] = board[fromX][fromY];
				board[fromX][fromY] = tempPiece;
				board[fromX][fromY].setBoardDisplay("x");
				//System.out.println(board[toX][toY].getDisplay());
				turn++;
			}else {
				System.out.println("Move Not Valid try again"
						+ "");
			}
		}

		
	}
	
	public void fillBoard() {
		for(int j = 0; j<8;j++) {
			for(int i = 0; i<8;i++) {
				board[i][j] = new Piece("open",false,i,j);
				board[i][j].setBoardDisplay("x");
			}
		}
	}
	//checks to see if the move is valid on the board, first pass to see if what was entered is a valid moive, will have second isValid for each peice.
	public boolean isValid(int fromX, int fromY, int toX, int toY) {
		if(fromX == toX && fromY == toY) {
			return false;
		}else if(toX < 0 || toX > 7 || fromX < 0 || fromX > 7 || toY < 0 || toY > 7 || fromY < 0 || fromY > 7) {
			return false;
		}else {
			return true;
		}
	}
	
	public boolean stillTwoKings() {
		int kingCount =0;
		for(int j = 0; j<8;j++) {
			for(int i = 0; i<8;i++) {
				if(board[i][j].getDisplay() =="K")
					kingCount++;
			}
		}
		if(kingCount == 2) {
			return true;
		}
		return false;
		
	}
	
	public boolean moveIsValid(int fromX, int fromY, int toX, int toY) {
		if(isValid(fromX,fromY,toX,toY)) { // checks validity of board movement and is gonna assume that players know the rules of chess.
			if((getTurn() % 2) == 0) {
				switch(board[fromX][fromY].getDisplay()){
				//white pieces
				case "p"://pawn
					if(!spotIsOpen(toX,toY) && fromX != toX && fromY != toY) {
						return true;
					}
					if((toY == (fromY + 2)) && toX == fromX && board[fromX][fromY].getFirstPawnMove())
						return true;
					if(toY == (fromY + 1) && toX == fromX)
							return true;
					break;
				case "R"://rook sure as hell not implementing rook king swap
					if(fromY == toY) {
						 return true;
					}
					if(fromX == toX) {
						return true;
					}
					
					break;
				case "k"://knight
			        if(toX != fromX - 1 && toX != fromX + 1 && toX != fromX + 2 && toX != fromX - 2)
			            return false;
			        if(toY != fromY - 2 && toY != fromY + 2 && toY != fromY - 1 && toY != fromY + 1)
			            return false;
			        return true;
				case "B"://bishop
					if(toX-fromX==toY-fromY) {
						return true;
					}
					break;
				case "Q"://queen
					if(fromY == toY) {
						 return true;
					}
					if(fromX == toX) {
						return true;
					}
					if(toX-fromX==toY-fromY) {
						return true;
					}
					break;
				case "K"://king
					if(fromY == toY && Math.abs(fromY-toY) == 1) {
						 return true;
					}
					if(fromX == toX&& Math.abs(fromX-toX) == 1) {
						return true;
					}
					if(toX-fromX==toY-fromY && Math.abs(fromY-toY) == 1) {
						return true;
					}
					break;
			
					}
				}
				
			if((getTurn() % 2) ==1 ) {
				switch(board[fromX][fromY].getDisplay()){
				//black pieces
				case "K"://king
					if(fromY == toY && Math.abs(fromY-toY) == 1) {
						 return true;
					}
					if(fromX == toX&& Math.abs(fromX-toX) == 1) {
						return true;
					}
					if(toX-fromX==toY-fromY && Math.abs(fromY-toY) == 1) {
						return true;
					}
					break;
				case "Q"://queen
					if(fromY == toY) {
						 return true;
					}
					if(fromX == toX) {
						return true;
					}
					if(toX-fromX==toY-fromY) {
						return true;
					}
					break;
				case "R"://rook
					if(fromY == toY) {
						 return true;
					}
					if(fromX == toX) {
						return true;
					}
					
					break;
				case "B"://bishop
					if(toX-fromX==toY-fromY) {
						return true;
					}
					break;
				case "k"://knight
					 if(toX != fromX - 1 && toX != fromX + 1 && toX != fromX + 2 && toX != fromX - 2)
				            return false;
				     if(toY != fromY - 2 && toY != fromY + 2 && toY != fromY - 1 && toY != fromY + 1)
				            return false;
				      return true;
					
				case "p"://pawn
					if(!spotIsOpen(toX,toY) && fromX != toX && fromY != toY) {
						return true;
					}
					if((toY == (fromY - 2)) && toX == fromX && board[fromX][fromY].getFirstPawnMove())
						return true;
					if(toY == (fromY - 1) && toX == fromX)
							return true;
					break;
				default: 
					return false;
				}
			}	
		}
		return false;
	}
	
	public int getTurn() {
		return turn;
	}
	
	public boolean spotIsOpen(int x, int y) { 
		if((board[x][y].getDisplay() != "x") && (x > 0 || x < 7 || y > 0 || y < 7)) {
			return false;
		}
		return true;
	}
	
	public void setPiece(Piece piece) {
		board[piece.getX()][piece.getY()] = piece;
	}
	
	public Piece[][] passBoard() {
		return board;
	}
	
}
