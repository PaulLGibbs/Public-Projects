//creates pieces needed and places them into the board
public class PieceFactory {
	GameManager gm = GameManager.getInstance();
	
	public PieceFactory(){
		
	}
	public void createBoard(){
		for(int i = 0;i<8;i++) {
			Piece whitePawn = new Piece("Pawn",true,i,1);
			gm.setPiece(whitePawn);
			Piece blackPawn = new Piece("Pawn",false,i,6);
			gm.setPiece(blackPawn);
		}
		//white pieces
		Piece whiteRook1 = new Piece("Rook",true,7,0);
		gm.setPiece(whiteRook1);
		Piece whiteRook2 = new Piece("Rook",true,0,0);
		gm.setPiece(whiteRook2);
		Piece whiteKnight1 = new Piece("Knight",true,1,0);
		gm.setPiece(whiteKnight1);
		Piece whiteKnight2 = new Piece("Knight",true,6,0);
		gm.setPiece(whiteKnight2);
		Piece whiteBishop1 = new Piece("Bishop",true,2,0);
		gm.setPiece(whiteBishop1);
		Piece whiteBishop2 = new Piece("Bishop",true,5,0);
		gm.setPiece(whiteBishop2);
		Piece whiteKing = new Piece("King",true,3,0);
		gm.setPiece(whiteKing);
		Piece whiteQueen = new Piece("Queen",true,4,0);
		gm.setPiece(whiteQueen);
		
		//black pieces
		Piece blackRook1 = new Piece("Rook",false,0,7);
		gm.setPiece(blackRook1);
		Piece blackRook2 = new Piece("Rook",false,7,7);
		gm.setPiece(blackRook2);
		Piece blackKnight1 = new Piece("Knight",false,1,7);
		gm.setPiece(blackKnight1);
		Piece blackKnight2 = new Piece("Knight",false,6,7);
		gm.setPiece(blackKnight2);
		Piece blackBishop1 = new Piece("Bishop",false,2,7);
		gm.setPiece(blackBishop1);
		Piece blackBishop2 = new Piece("Bishop",false,5,7);
		gm.setPiece(blackBishop2);
		Piece blackKing = new Piece("King",false,3,7);
		gm.setPiece(blackKing);
		Piece blackQueen = new Piece("Queen",false,4,7);
		gm.setPiece(blackQueen);
	}
}
