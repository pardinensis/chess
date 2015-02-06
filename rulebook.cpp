//#include "rolebook.hpp"

#include <iostream>
#include <map>
#include <vector>
#include <string>

std::map<int, std::vector<int>> possible_moves;


void generate_king_moves(int pos, char* fboard, char* oboard) {
	int posx = pos % 8;
	int posy = pos / 8;
	for (int x = posx-1; x <= posx+1; ++x) {
		if (x < 0 || x > 8) continue;
		for (int y = posy-1; y <= posy+1; ++y) {
			if (y < 0 || y > 8) continue;
			int new_pos = y * 8 + x;
			if (new_pos == pos) continue;
			if (fboard[new_pos] == ' ') {
				possible_moves[pos].push_back(new_pos);
			}
		}
	}

	// TODO: rochade
}

void generate_rook_moves(int pos, char* fboard, char* oboard) {
	int posx = pos % 8;
	int posy = pos / 8;
	int new_pos;
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
	for (int y = posy - 1; y >= 0; --y) {
		int new_pos = y * 8 + posx;
		if (fboard[new_pos] != ' ') break;
		possible_moves[pos].push_back(new_pos);
		if (oboard[new_pos] != ' ') break;
	}
	for (int y = posy + 1; y < 8; ++y) {
		int new_pos = y * 8 + posx;
		if (fboard[new_pos] != ' ') break;
		possible_moves[pos].push_back(new_pos);
		if (oboard[new_pos] != ' ') break;
	}
}

void generate_bishop_moves(int pos, char* fboard, char* oboard) {
	int posx = pos % 8;
	int posy = pos / 8;
	for (int x = posx - 1,y = posy - 1; x >= 0 && y >= 0; --x,--y) {
		int new_pos = y * 8 + x;
		if (fboard[new_pos] != ' ') break;
		possible_moves[pos].push_back(new_pos);
		if (oboard[new_pos] != ' ') break;
	}
	for (int x = posx + 1,y = posy - 1; x < 8 && y >= 0; ++x,--y) {
		int new_pos = y * 8 + x;
		if (fboard[new_pos] != ' ') break;
		possible_moves[pos].push_back(new_pos);
		if (oboard[new_pos] != ' ') break;
	}
	for (int x = posx - 1,y = posy + 1; x >= 0 && y < 8; --x,++y) {
		int new_pos = y * 8 + x;
		if (fboard[new_pos] != ' ') break;
		possible_moves[pos].push_back(new_pos);
		if (oboard[new_pos] != ' ') break;
	}
	for (int x = posx + 1,y = posy + 1; x < 8 && y < 8; ++x,++y) {
		int new_pos = y * 8 + x;
		if (fboard[new_pos] != ' ') break;
		possible_moves[pos].push_back(new_pos);
		if (oboard[new_pos] != ' ') break;
	}
}

void generate_knight_moves(int pos, char* fboard, char* oboard) {
	int posx = pos % 8;
	int posy = pos / 8;
	int new_posx=-1;
	int new_posy=-1;
	for (int i = 0; i < 8; ++i) {
		new_posy = posy + (i%2+1)*(i/4*2-1);
		new_posx = posx + ((i+1)%2+1)*(((i/2)%2)*2-1);
		if (new_posx >= 0 && new_posy >= 0 && new_posx < 8 && new_posy < 8) {
			int new_pos = new_posy * 8 + new_posx;
			if (fboard[new_pos] == ' ') possible_moves[pos].push_back(new_pos);
		}
	}
}

void generate_pawn_moves(int pos, char* fboard, char* oboard) {
	int posx = pos % 8;
	int posy = pos / 8;
	if (posy < 7) {
		// moving forward
		int ahead = pos + 8;
		if (fboard[ahead] == ' ' && oboard[ahead] == ' ') {
			possible_moves[pos].push_back(ahead);
			if (posy == 1) {
				int ahead2 = pos + 16;
				if (fboard[ahead2] == ' ' && oboard[ahead2] == ' ')
					possible_moves[pos].push_back(ahead2);
			}
		}
		
		// capturing
		if (posx > 0) {
			int diagonal = pos + 7;
			if (fboard[diagonal] == ' ' && oboard[diagonal] != ' ')
				possible_moves[pos].push_back(diagonal);
		}
		if (posx < 7) {
			int diagonal = pos + 9;
			if (fboard[diagonal] == ' ' && oboard[diagonal] != ' ')
				possible_moves[pos].push_back(diagonal);
		}
	}

	// TODO: en passant
	// TODO: promotion
}

void generate_possible_moves(char* fboard, char* oboard) {
	possible_moves.clear();

	for (int i = 0; i < 64; ++i) {
		possible_moves[i] = std::vector<int>();
		
		switch(fboard[i]) {
			case 'K':
				generate_king_moves(i, fboard, oboard);
				break;
			case 'Q':
				generate_rook_moves(i, fboard, oboard);
				generate_bishop_moves(i, fboard, oboard);
				break;
			case 'R':
				generate_rook_moves(i, fboard, oboard);
				break;
			case 'B':
				generate_bishop_moves(i, fboard, oboard);
				break;
			case 'N':
				generate_knight_moves(i, fboard, oboard);
				break;
			case 'P':
				generate_pawn_moves(i, fboard, oboard);
		}
	}
}

void generate_possible_moves(char* white_board, char* black_board, bool white) {
	char* fboard = new char[64];
	char* oboard = new char[64];

	if (white) {
		for (int i = 0; i < 64; ++i) {
			fboard[i] = white_board[i];
			oboard[i] = black_board[i];
		}
	} else {
		for (int i = 0; i < 64; ++i) {
			fboard[i] = black_board[63 - i];
			oboard[i] = white_board[63 - i];
		}
	}

	generate_possible_moves(fboard, oboard);

	delete[] fboard;
	delete[] oboard;
}

std::string pos_to_string(int pos) {
	int posx = pos % 8;
	int posy = pos / 8;
	char x = 'a' + posx;
	char y = '1' + posy;
	std::string str;
	str += x;
	str += y;
	return str;	
}

int main(int argc, char** argv) {
	char white_board [64] = {
		'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R',
		'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
	};
	char black_board [64] = {
	};


	for (int i = 0; i < 64; ++i) {
		if (white_board[i] == 0)
			white_board[i] = ' ';
		if (black_board[i] == 0)
			black_board[i] = ' ';
	}

	generate_possible_moves(white_board, black_board, true);

	for (int i = 0; i < 64; ++i) {
		if (possible_moves[i].empty())
			continue;

		char piece = white_board[i];
		for (int j = 0; j < possible_moves[i].size(); ++j) {
			std::cout << piece << " from " << pos_to_string(i) << 
			" to " << pos_to_string(possible_moves[i][j]) << std::endl;
		}
	}

	return 0;
}