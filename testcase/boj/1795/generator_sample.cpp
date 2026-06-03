#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

void putRandomPiece(vector<string>& board) {
    int n = (int)board.size();
    int m = (int)board[0].size();
    board[rnd.next(n)][rnd.next(m)] = char('1' + rnd.next(9));
}

void fillPieces(vector<string>& board, int targetPieces, int minSpeed, int maxSpeed) {
    int n = (int)board.size();
    int m = (int)board[0].size();
    targetPieces = min(targetPieces, n * m);

    vector<int> cells;
    for (int i = 0; i < n * m; ++i) {
        cells.push_back(i);
    }
    shuffle(cells.begin(), cells.end());

    for (int i = 0; i < targetPieces; ++i) {
        int cell = cells[i];
        board[cell / m][cell % m] = char('0' + rnd.next(minSpeed, maxSpeed));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    int m;
    vector<string> board;

    if (mode == 0) {
        n = rnd.next(1, 3);
        m = rnd.next(1, 3);
        board.assign(n, string(m, '.'));
        putRandomPiece(board);
    } else if (mode == 1) {
        n = rnd.next(1, 2);
        m = rnd.next(4, 10);
        if (rnd.next(2)) {
            swap(n, m);
        }
        board.assign(n, string(m, '.'));
        int pieces = rnd.next(2, min(n * m, 5));
        fillPieces(board, pieces, 1, 3);
    } else if (mode == 2) {
        n = rnd.next(4, 10);
        m = rnd.next(4, 10);
        board.assign(n, string(m, '.'));
        int pieces = rnd.next(2, min(n * m, 8));
        fillPieces(board, pieces, 1, 9);
    } else if (mode == 3) {
        n = rnd.next(5, 10);
        m = rnd.next(5, 10);
        board.assign(n, string(m, '.'));
        int pieces = rnd.next(n * m / 2, n * m);
        fillPieces(board, pieces, 1, 9);
    } else if (mode == 4) {
        n = rnd.next(3, 10);
        m = rnd.next(3, 10);
        board.assign(n, string(m, '.'));
        board[0][0] = char('1' + rnd.next(9));
        board[0][m - 1] = char('1' + rnd.next(9));
        board[n - 1][0] = char('1' + rnd.next(9));
        board[n - 1][m - 1] = char('1' + rnd.next(9));
        int extra = rnd.next(0, min(n * m - 4, 6));
        fillPieces(board, 4 + extra, 1, 9);
    } else {
        n = rnd.next(8, 10);
        m = rnd.next(8, 10);
        board.assign(n, string(m, '.'));
        int pieces = rnd.next(10, min(n * m, 25));
        int lo = rnd.next(1, 7);
        int hi = rnd.next(lo, 9);
        fillPieces(board, pieces, lo, hi);
    }

    println(n, m);
    for (const string& row : board) {
        println(row);
    }

    return 0;
}
