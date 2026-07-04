#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;

struct Board {
    int h;
    int w;
    vector<vector<pair<int, int>>> pairs;
    vector<pair<int, int>> boundaryStarts;
};

int squareIndex(int row, int col, int w) {
    return row * w + col;
}

bool isBoundaryPoint(int row, int col, int point, int h, int w) {
    if ((point == 0 || point == 1) && row == 0) return true;
    if ((point == 2 || point == 3) && col + 1 == w) return true;
    if ((point == 4 || point == 5) && row + 1 == h) return true;
    if ((point == 6 || point == 7) && col == 0) return true;
    return false;
}

string pointName(int square, int point) {
    return to_string(square + 1) + char('A' + point);
}

void addPair(Board& board, int row, int col, int a, int b) {
    if (a > b) swap(a, b);
    board.pairs[squareIndex(row, col, board.w)].push_back({a, b});
}

void addHorizontalPath(Board& board, int row, bool upperLane) {
    int left = upperLane ? 7 : 6;
    int right = upperLane ? 2 : 3;
    for (int col = 0; col < board.w; ++col) {
        addPair(board, row, col, left, right);
    }
    board.boundaryStarts.push_back({squareIndex(row, 0, board.w), left});
    board.boundaryStarts.push_back({squareIndex(row, board.w - 1, board.w), right});
}

void addVerticalPath(Board& board, int col, bool leftLane) {
    int top = leftLane ? 0 : 1;
    int bottom = leftLane ? 5 : 4;
    for (int row = 0; row < board.h; ++row) {
        addPair(board, row, col, top, bottom);
    }
    board.boundaryStarts.push_back({squareIndex(0, col, board.w), top});
    board.boundaryStarts.push_back({squareIndex(board.h - 1, col, board.w), bottom});
}

void addLocalBoundaryPair(Board& board, int row, int col) {
    vector<int> points;
    set<int> used;
    int square = squareIndex(row, col, board.w);
    for (auto [a, b] : board.pairs[square]) {
        used.insert(a);
        used.insert(b);
    }

    for (int point = 0; point < 8; ++point) {
        if (!used.count(point) && isBoundaryPoint(row, col, point, board.h, board.w)) {
            points.push_back(point);
        }
    }
    if (points.size() < 2) return;

    shuffle(points.begin(), points.end());
    int a = points[0];
    int b = points[1];
    addPair(board, row, col, a, b);
    board.boundaryStarts.push_back({square, a});
    board.boundaryStarts.push_back({square, b});
}

Board makeBoard(int h, int w) {
    Board board;
    board.h = h;
    board.w = w;
    board.pairs.assign(h * w, {});

    if (w >= 2) {
        vector<int> rows(h);
        for (int i = 0; i < h; ++i) rows[i] = i;
        shuffle(rows.begin(), rows.end());
        int rowCount = rnd.next(1, h);
        for (int i = 0; i < rowCount; ++i) {
            addHorizontalPath(board, rows[i], rnd.next(0, 1) == 1);
        }
    }

    if (h >= 2) {
        vector<int> cols(w);
        for (int i = 0; i < w; ++i) cols[i] = i;
        shuffle(cols.begin(), cols.end());
        int colCount = rnd.next(1, w);
        for (int i = 0; i < colCount; ++i) {
            addVerticalPath(board, cols[i], rnd.next(0, 1) == 1);
        }
    }

    int localCount = rnd.next(0, min(3, h * w));
    for (int i = 0; i < localCount; ++i) {
        int row = rnd.next(0, h - 1);
        int col = rnd.next(0, w - 1);
        addLocalBoundaryPair(board, row, col);
    }

    for (auto& squarePairs : board.pairs) {
        sort(squarePairs.begin(), squarePairs.end());
        squarePairs.erase(unique(squarePairs.begin(), squarePairs.end()), squarePairs.end());
    }
    sort(board.boundaryStarts.begin(), board.boundaryStarts.end());
    board.boundaryStarts.erase(unique(board.boundaryStarts.begin(), board.boundaryStarts.end()),
                               board.boundaryStarts.end());
    shuffle(board.boundaryStarts.begin(), board.boundaryStarts.end());
    return board;
}

void printBoard(const Board& board) {
    println(board.h, board.w);

    vector<int> described;
    for (int square = 0; square < board.h * board.w; ++square) {
        if (!board.pairs[square].empty()) described.push_back(square);
    }
    shuffle(described.begin(), described.end());

    for (int square : described) {
        printf("%d", square + 1);
        for (auto [a, b] : board.pairs[square]) {
            printf(" %c%c", char('A' + a), char('A' + b));
        }
        printf("\n");
    }
    println(0);

    int startCount = rnd.next(1, min<int>(board.boundaryStarts.size(), 8));
    vector<string> starts;
    for (int i = 0; i < startCount; ++i) {
        starts.push_back(pointName(board.boundaryStarts[i].first, board.boundaryStarts[i].second));
    }
    println(starts);
    printf("\n");
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int boardCount = rnd.next(2, 4);
    for (int i = 0; i < boardCount; ++i) {
        int mode = rnd.next(0, 3);
        int h = 1;
        int w = 1;
        if (mode == 0) {
            w = rnd.next(1, 6);
        } else if (mode == 1) {
            h = rnd.next(1, 6);
        } else {
            h = rnd.next(2, 4);
            w = rnd.next(2, 5);
        }

        Board board = makeBoard(h, w);
        if (board.boundaryStarts.empty()) {
            addLocalBoundaryPair(board, 0, 0);
        }
        printBoard(board);
    }
    println(0, 0);

    return 0;
}
