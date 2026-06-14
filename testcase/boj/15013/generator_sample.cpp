#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

static void setWin(vector<string>& board, int winner, int loser) {
    board[winner][loser] = '1';
    board[loser][winner] = '0';
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode <= 3) {
        n = rnd.next(2, 12);
    } else {
        n = rnd.next(13, 24);
    }

    vector<string> board(n, string(n, '0'));
    for (int i = 0; i < n; ++i) board[i][i] = 'X';

    if (mode == 0) {
        // Single player edge case.
    } else if (mode == 1) {
        vector<int> order(n);
        for (int i = 0; i < n; ++i) order[i] = i;
        shuffle(order.begin(), order.end());

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                setWin(board, order[i], order[j]);
            }
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            for (int step = 1; step <= (n - 1) / 2; ++step) {
                setWin(board, i, (i + step) % n);
            }
        }
        if (n % 2 == 0) {
            for (int i = 0; i < n / 2; ++i) {
                if (rnd.next(0, 1)) {
                    setWin(board, i, i + n / 2);
                } else {
                    setWin(board, i + n / 2, i);
                }
            }
        }
    } else if (mode == 3) {
        int split = rnd.next(1, n - 1);
        vector<int> strong, weak;
        for (int i = 0; i < n; ++i) {
            if (i < split) strong.push_back(i);
            else weak.push_back(i);
        }
        shuffle(strong.begin(), strong.end());
        shuffle(weak.begin(), weak.end());

        for (int x : strong) {
            for (int y : weak) setWin(board, x, y);
        }
        for (const vector<int>* group : {&strong, &weak}) {
            for (int i = 0; i < (int)group->size(); ++i) {
                for (int j = i + 1; j < (int)group->size(); ++j) {
                    if (rnd.next(0, 1)) setWin(board, (*group)[i], (*group)[j]);
                    else setWin(board, (*group)[j], (*group)[i]);
                }
            }
        }
    } else {
        double p = rnd.next(0.15, 0.85);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (rnd.next() < p) setWin(board, i, j);
                else setWin(board, j, i);
            }
        }
    }

    if (n > 1 && mode != 0) {
        int henkBias = rnd.next(0, 3);
        if (henkBias == 0) {
            for (int j = 1; j < n; ++j) setWin(board, 0, j);
        } else if (henkBias == 1) {
            for (int j = 1; j < n; ++j) setWin(board, j, 0);
        } else if (henkBias == 2) {
            vector<int> opponents;
            for (int j = 1; j < n; ++j) opponents.push_back(j);
            shuffle(opponents.begin(), opponents.end());
            int wins = rnd.next(1, n - 1);
            for (int k = 0; k < (int)opponents.size(); ++k) {
                if (k < wins) setWin(board, 0, opponents[k]);
                else setWin(board, opponents[k], 0);
            }
        }
    }

    println(n);
    for (const string& row : board) println(row);

    return 0;
}
