#pragma once

class Board {
private:
	
	// 'P' = Pawn
	// 'N' = Knight
	// 'B' = Bishop
	// 'R' = Rook
	// 'Q' = Queen
	// 'K' = King
	// ' ' = empty

	char* white_board;
	char* black_board;

public:
	Board();
	~Board();

	bool is_chessman(char type);

	bool move_chessman(bool white, char type, int from, int to);
};