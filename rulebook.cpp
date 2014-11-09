#include "rolebook.hpp"

std::map<int, std::vector<int>> possible_moves;


void generate_rook_moves(int pos, char* fboard, char*oboard) {
	int posx = pos % 8;
	int posy = pos / 8;
	for (int x = posx - 1; x >= 0; --x) {
		int new_pos = posy * 8 + x;
		if (fboard[new_pos] != ' ') break;
		possible_moves[pos].push_back(new_pos);
		if (oboard[new_pos] != ' ') break;
	}
	for (int x = posx + 1; x < 8; ++x) {
		int new_pos = posy * 8 + x;
		if (fboard[new_pos] != ' ') break;
		possible_moves[pos].push_back(new_pos);
		if (oboard[new_pos] != ' ') break;
	}
	for (int y = posy - 1; y >= 0; --x) {
		int new_pos = y * 8 + posx;
		if (fboard[new_pos] != ' ') break;
		possible_moves[pos].push_back(new_pos);
		if (oboard[new_pos] != ' ') break;
	}
	for (int y = posy + 1; y < 8; ++x) {
		int new_pos = y * 8 + posx;
		if (fboard[new_pos] != ' ') break;
		possible_moves[pos].push_back(new_pos);
		if (oboard[new_pos] != ' ') break;
	}
}

void generate_possible_moves(char* fboard, char*oboard) {
	possible_moves.clear();

	for (int i = 0; i < 64; ++i) {
		fboard[i] = std::vector<int>();
		
		if (board[i] == 'R')
			generate_rook_moves(i, fboard, oboard);
	}
}