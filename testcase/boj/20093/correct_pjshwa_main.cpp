#include "coins.h"

int B[6];
int board[8][8];

int cal() {
	int pw = 1, ret = 0;
	for (int k = 0; k < 6; k++) {
		ret += pw * B[k];
		pw *= 2;
	}
	return ret;
}

std::vector<int> coin_flips(std::vector<int> b, int c) {
	for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++) board[i][j] = b[i * 8 + j];

	std::vector<int> flips(1);
	for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++) {
		board[i][j] ^= 1;

		for (int k = 0; k < 6; k++) B[k] = 0;
		for (int ui = 0; ui < 8; ui++) for (int uj = 0; uj < 8; uj++) for (int k = 0; k < 6; k++) {
			int u = ui * 8 + uj;
			if (u & (1 << k)) B[k] ^= board[ui][uj];
		}

		if (cal() == c) {
			flips[0] = i * 8 + j;
			return flips;
		}
		board[i][j] ^= 1;
	}
	return flips;
}

int find_coin(std::vector<int> b) {
	for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++) board[i][j] = b[i * 8 + j];
	for (int k = 0; k < 6; k++) B[k] = 0;
	for (int ui = 0; ui < 8; ui++) for (int uj = 0; uj < 8; uj++) for (int k = 0; k < 6; k++) {
		int u = ui * 8 + uj;
		if (u & (1 << k)) B[k] ^= board[ui][uj];
	}
	return cal();
}
