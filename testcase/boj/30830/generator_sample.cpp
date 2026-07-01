#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

using Cell = pair<int, int>;

void addCell(vector<Cell>& board, set<Cell>& used, int x, int y) {
    if (used.insert({x, y}).second) {
        board.push_back({x, y});
    }
}

void fillRandom(vector<Cell>& board, set<Cell>& used, int n) {
    while ((int)board.size() < n) {
        addCell(board, used, rnd.next(1, n), rnd.next(1, n));
    }
}

vector<Cell> shuffledPermutationBoard(int n) {
    vector<int> cols;
    for (int i = 1; i <= n; ++i) {
        cols.push_back(i);
    }
    shuffle(cols.begin(), cols.end());

    vector<Cell> board;
    for (int row = 1; row <= n; ++row) {
        board.push_back({row, cols[row - 1]});
    }
    shuffle(board.begin(), board.end());
    return board;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = 1;
    vector<Cell> first;
    vector<Cell> second;
    set<Cell> usedFirst;
    set<Cell> usedSecond;

    if (mode == 0) {
        n = rnd.next(1, 4);
        first = shuffledPermutationBoard(n);
        second = first;
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        first = shuffledPermutationBoard(n);
        second = shuffledPermutationBoard(n);
    } else if (mode == 2) {
        n = rnd.next(2, 9);
        int heavyRow = rnd.next(1, n);
        int heavyCol = rnd.next(1, n);
        for (int col = 1; col <= n && (int)first.size() < n; ++col) {
            addCell(first, usedFirst, heavyRow, col);
        }
        for (int row = 1; row <= n && (int)second.size() < n; ++row) {
            addCell(second, usedSecond, row, heavyCol);
        }
        fillRandom(first, usedFirst, n);
        fillRandom(second, usedSecond, n);
    } else if (mode == 3) {
        n = rnd.next(3, 10);
        int block = rnd.next(2, n);
        for (int i = 1; i <= block && (int)first.size() < n; ++i) {
            addCell(first, usedFirst, i, rnd.next(1, block));
            addCell(second, usedSecond, rnd.next(1, block), i);
        }
        fillRandom(first, usedFirst, n);
        fillRandom(second, usedSecond, n);
    } else if (mode == 4) {
        n = rnd.next(2, 12);
        for (int i = 1; i <= n; ++i) {
            int x = i;
            int y = rnd.next(1, n);
            addCell(first, usedFirst, x, y);
            addCell(second, usedSecond, x, y);
        }
        fillRandom(first, usedFirst, n);
        fillRandom(second, usedSecond, n);
    } else {
        n = rnd.next(2, 12);
        fillRandom(first, usedFirst, n);
        fillRandom(second, usedSecond, n);
    }

    shuffle(first.begin(), first.end());
    shuffle(second.begin(), second.end());

    println(n);
    for (const Cell& cell : first) {
        println(cell.first, cell.second);
    }
    for (const Cell& cell : second) {
        println(cell.first, cell.second);
    }

    return 0;
}
