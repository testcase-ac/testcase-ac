#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct GridCase {
    int r;
    int c;
    vector<string> rows;
};

pair<int, int> randomCell(int r, int c) {
    return {rnd.next(0, r - 1), rnd.next(0, c - 1)};
}

GridCase makeCase(int mode) {
    int r;
    int c;

    if (mode == 0) {
        if (rnd.next(2) == 0) {
            r = 1;
            c = rnd.next(2, 8);
        } else {
            r = rnd.next(2, 8);
            c = 1;
        }
    } else if (mode == 1) {
        r = rnd.next(2, 4);
        c = rnd.next(2, 4);
    } else if (mode == 2) {
        r = rnd.next(5, 8);
        c = rnd.next(5, 8);
    } else if (mode == 3) {
        r = rnd.next(2, 8);
        c = rnd.next(2, 8);
    } else {
        r = rnd.any(vector<int>{1, 2, 7, 8});
        c = rnd.any(vector<int>{1, 2, 7, 8});
        if (r * c == 1) c = 2;
    }

    vector<string> rows(r, string(c, '.'));

    double wallProbability;
    if (mode == 0) {
        wallProbability = rnd.next(0.0, 0.35);
    } else if (mode == 1) {
        wallProbability = rnd.next(0.0, 0.25);
    } else if (mode == 2) {
        wallProbability = rnd.next(0.35, 0.70);
    } else if (mode == 3) {
        wallProbability = rnd.next(0.15, 0.50);
    } else {
        wallProbability = rnd.next(0.0, 0.65);
    }

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (rnd.next() < wallProbability) rows[i][j] = '#';
        }
    }

    if (mode == 3) {
        int corridorRow = rnd.next(0, r - 1);
        int corridorCol = rnd.next(0, c - 1);
        for (int j = 0; j < c; ++j) rows[corridorRow][j] = '.';
        for (int i = 0; i < r; ++i) rows[i][corridorCol] = '.';
    }

    vector<pair<int, int>> cells;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            cells.push_back({i, j});
        }
    }
    shuffle(cells.begin(), cells.end());

    pair<int, int> start = cells[0];
    pair<int, int> cake = cells[1];
    if (rnd.next(4) == 0) {
        start = randomCell(r, c);
        do {
            cake = randomCell(r, c);
        } while (cake == start);
    }

    rows[start.first][start.second] = 'O';
    rows[cake.first][cake.second] = 'X';

    return {r, c, rows};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int t = 200;
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        GridCase g = makeCase(rnd.next(0, 4));
        println(g.r, g.c);
        for (const string& row : g.rows) {
            println(row);
        }
    }

    return 0;
}
