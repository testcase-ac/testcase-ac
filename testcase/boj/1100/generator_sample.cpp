#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> board(8, string(8, '.'));
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        double p = rnd.next(0.0, 0.25);
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (rnd.next() < p) board[i][j] = 'F';
            }
        }
    } else if (mode == 1) {
        double p = rnd.next(0.65, 1.0);
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (rnd.next() < p) board[i][j] = 'F';
            }
        }
    } else if (mode == 2) {
        double whiteProb = rnd.next(0.35, 1.0);
        double blackProb = rnd.next(0.0, 0.20);
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                double p = ((i + j) % 2 == 0) ? whiteProb : blackProb;
                if (rnd.next() < p) board[i][j] = 'F';
            }
        }
    } else if (mode == 3) {
        double whiteProb = rnd.next(0.0, 0.20);
        double blackProb = rnd.next(0.35, 1.0);
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                double p = ((i + j) % 2 == 0) ? whiteProb : blackProb;
                if (rnd.next() < p) board[i][j] = 'F';
            }
        }
    } else if (mode == 4) {
        bool rows = rnd.next(0, 1);
        int parity = rnd.next(0, 1);
        double noise = rnd.next(0.0, 0.15);
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                bool selected = rows ? (i % 2 == parity) : (j % 2 == parity);
                if (selected || rnd.next() < noise) board[i][j] = 'F';
            }
        }
    } else {
        int parity = rnd.next(0, 1);
        double flipProb = rnd.next(0.0, 0.18);
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                bool selected = ((i + j) % 2 == parity);
                if (rnd.next() < flipProb) selected = !selected;
                if (selected) board[i][j] = 'F';
            }
        }
    }

    for (const string& row : board) {
        println(row);
    }

    return 0;
}
