#include "board.hpp"

Board::Board() {
	white_board = new char[64];
	black_board = new char[64];
}

Board::~Board() {
	delete [] white_board;
	delete [] black_board;
}


bool Board::is_chessman(char type) {
	switch (type) {
		case 'P':
		case 'N':
		case 'B':
		case 'R':
		case 'Q':
		case 'K':
			return true;
		default:
			return false;
	}
}

bool Board::move_chessman(bool white, char type, int from, int to) {
	// check coordinates
	if (from < 0 || from >= 64)	return false;
	if (to   < 0 || to   >= 64) return false;

	// check type
	if (!is_chessman(type)) return false;

	// check board
	char* board = (white) ? white_board : black_board;
	if (board[from] != type) return false;
	if (is_chessman(board[to])) return false;

	// check rules
	return false;
}


int main() {} // temporary