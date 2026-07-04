#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

namespace {

using Board = vector<vector<int>>;

vector<pair<int, int>> lineCells(int n, int type, int index) {
    vector<pair<int, int>> cells;
    if (type == 0) {
        for (int j = 0; j < n; ++j) cells.push_back({index, j});
    } else if (type == 1) {
        for (int i = 0; i < n; ++i) cells.push_back({i, index});
    } else if (type == 2) {
        for (int i = 0; i < n; ++i) cells.push_back({i, i});
    } else {
        for (int i = 0; i < n; ++i) cells.push_back({i, n - 1 - i});
    }
    return cells;
}

vector<int> valuesFromCells(const Board& board, const vector<pair<int, int>>& cells) {
    vector<int> values;
    for (auto [r, c] : cells) values.push_back(board[r][c]);
    return values;
}

void appendUnique(vector<int>& draws, set<int>& used, const vector<int>& values) {
    vector<int> shuffled = values;
    shuffle(shuffled.begin(), shuffled.end());
    for (int value : shuffled) {
        if (used.insert(value).second) draws.push_back(value);
    }
}

int freshValue(set<int>& used) {
    int value = rnd.next(1, 1000000);
    while (!used.insert(value).second) value = rnd.next(1, 1000000);
    return value;
}

Board makeBoard(int n, int start) {
    Board board(n, vector<int>(n));
    int value = start;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) board[i][j] = value++;
    }

    vector<int> flat;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) flat.push_back(board[i][j]);
    }
    shuffle(flat.begin(), flat.end());

    int p = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) board[i][j] = flat[p++];
    }
    return board;
}

void printBoard(const Board& board) {
    for (const auto& row : board) println(row);
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = mode == 0 ? 1 : rnd.next(2, 8);
    int u = rnd.next(1, min(13, 2 * n + 2));
    int v = rnd.next(1, min(13, 2 * n + 2));

    Board usagi = makeBoard(n, 1);
    Board neko = rnd.next(0, 1) ? makeBoard(n, 1) : makeBoard(n, 500001);

    int usagiType = rnd.next(0, 3);
    int nekoType = rnd.next(0, 3);
    int usagiIndex = rnd.next(0, n - 1);
    int nekoIndex = rnd.next(0, n - 1);

    vector<int> usagiLine = valuesFromCells(usagi, lineCells(n, usagiType, usagiIndex));
    vector<int> nekoLine = valuesFromCells(neko, lineCells(n, nekoType, nekoIndex));

    vector<int> draws;
    set<int> drawnValues;
    set<int> allUsed;
    for (const auto& row : usagi) {
        for (int value : row) allUsed.insert(value);
    }
    for (const auto& row : neko) {
        for (int value : row) allUsed.insert(value);
    }

    if (mode == 0) {
        appendUnique(draws, drawnValues, vector<int>{usagi[0][0]});
    } else if (mode == 1) {
        appendUnique(draws, drawnValues, usagiLine);
        appendUnique(draws, drawnValues, nekoLine);
    } else if (mode == 2) {
        appendUnique(draws, drawnValues, nekoLine);
        appendUnique(draws, drawnValues, usagiLine);
    } else {
        vector<int> mixed = usagiLine;
        mixed.insert(mixed.end(), nekoLine.begin(), nekoLine.end());
        shuffle(mixed.begin(), mixed.end());
        appendUnique(draws, drawnValues, mixed);
    }

    int extra = mode == 0 ? 0 : rnd.next(0, min(12, n * n));
    for (int i = 0; i < extra; ++i) {
        int value = freshValue(allUsed);
        if (drawnValues.insert(value).second) draws.push_back(value);
    }

    int m = static_cast<int>(draws.size());

    println(n, u, v, m);
    printBoard(usagi);
    printBoard(neko);
    for (int value : draws) println(value);

    return 0;
}
