#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Pos = pair<int, int>;

vector<Pos> allPositions() {
    vector<Pos> cells;
    for (int r = 1; r <= 8; ++r) {
        for (int c = 1; c <= 8; ++c) {
            cells.emplace_back(r, c);
        }
    }
    return cells;
}

vector<Pos> knightNeighbors(Pos p) {
    static const int dr[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    static const int dc[] = {-1, 1, -2, 2, -2, 2, -1, 1};

    vector<Pos> neighbors;
    for (int i = 0; i < 8; ++i) {
        int nr = p.first + dr[i];
        int nc = p.second + dc[i];
        if (1 <= nr && nr <= 8 && 1 <= nc && nc <= 8) {
            neighbors.emplace_back(nr, nc);
        }
    }
    return neighbors;
}

Pos randomFrom(const vector<Pos>& cells) {
    return cells[rnd.next(static_cast<int>(cells.size()))];
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Pos> cells = allPositions();
    vector<Pos> corners = {{1, 1}, {1, 8}, {8, 1}, {8, 8}};
    vector<Pos> edges;
    vector<Pos> interior;

    for (Pos p : cells) {
        if (p.first == 1 || p.first == 8 || p.second == 1 || p.second == 8) {
            edges.push_back(p);
        } else {
            interior.push_back(p);
        }
    }

    Pos white = randomFrom(cells);
    Pos black = randomFrom(cells);
    int mode = rnd.next(5);

    if (mode == 0) {
        white = randomFrom(corners);
        black = randomFrom(corners);
    } else if (mode == 1) {
        white = randomFrom(edges);
        black = randomFrom(interior);
    } else if (mode == 2) {
        white = randomFrom(cells);
        vector<Pos> neighbors = knightNeighbors(white);
        black = randomFrom(neighbors);
    } else if (mode == 3) {
        int color = rnd.next(2);
        vector<Pos> sameColor;
        for (Pos p : cells) {
            if ((p.first + p.second) % 2 == color) {
                sameColor.push_back(p);
            }
        }
        white = randomFrom(sameColor);
        black = randomFrom(sameColor);
    }

    while (white == black) {
        black = randomFrom(cells);
    }

    if (rnd.next(2)) {
        swap(white, black);
    }

    println(white.first, white.second);
    println(black.first, black.second);

    return 0;
}
