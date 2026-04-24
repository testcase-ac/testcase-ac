#include <iostream>

using namespace std;


int sudoku[9][9];
int checkRow[9][10];
int checkCol[9][10];
int checkSquare[3][3][10];
bool found = false;

bool check(int row, int col, int num) {
	return !checkRow[row][num] && !checkCol[col][num] && !checkSquare[row/3][col/3][num];
}

void checkPossibleAnswer(int row, int col) {
	if (col == 9) {
		row++; col = 0;
	}
	//cout<<"called function "<<row<<' '<<col<<' '<<endl;
	//	print();
	if (row == 9 && col == 0) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				cout << sudoku[i][j] << ' ';
			}
			cout << endl;
		}
		exit(0);
	}
	else {
		if (sudoku[row][col] == 0) {
			for (int i = 1; i < 10; i++) {
				if (check(row, col, i)) {
					sudoku[row][col] = i;
					checkRow[row][i] = 1;
					checkCol[col][i] = 1;
					checkSquare[row / 3][col / 3][i] = 1;
					checkPossibleAnswer(row, col + 1);
					sudoku[row][col] = 0;
					checkRow[row][i] = 0;
					checkCol[col][i] = 0;
					checkSquare[row / 3][col / 3][i] = 0;
				}

			}
		}
		else {
			checkPossibleAnswer(row, col + 1);
		}
	}
}


int main() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cin >> sudoku[i][j];
			checkRow[i][sudoku[i][j]] = 1;
			checkCol[j][sudoku[i][j]] = 1;
			checkSquare[i/3][j/3][sudoku[i][j]] = 1;
		}
	}

	checkPossibleAnswer(0, 0);
	return 0;
}