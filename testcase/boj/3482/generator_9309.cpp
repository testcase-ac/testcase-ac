#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <cstdio>

using namespace std;

void printSample() {
    // Problem statement sample input with 2 test cases
    println(2);
    // First case
    println(3, 3);
    printf("###\n");
    printf("#.#\n");
    printf("###\n");
    // Second case
    println(7, 6);
    printf("#######\n");
    printf("#.#.###\n");
    printf("#.#.###\n");
    printf("#.#.#.#\n");
    printf("#.....#\n");
    printf("#######\n");
}

vector<string> buildRandomTreeLabyrinth(int R, int C) {
    vector<string> grid(R, string(C, '#'));
    vector<vector<int>> adjDots(R, vector<int>(C, 0));
    vector<pair<int,int>> frontier;

    auto inside = [&](int r, int c) {
        return (r >= 0 && r < R && c >= 0 && c < C);
    };

    auto addNeighbor = [&](int r, int c) {
        static const int dr[4] = {-1, 1, 0, 0};
        static const int dc[4] = {0, 0, -1, 1};
        for (int k = 0; k < 4; ++k) {
            int nr = r + dr[k];
            int nc = c + dc[k];
            if (!inside(nr, nc)) continue;
            if (grid[nr][nc] == '#') {
                adjDots[nr][nc]++;
                if (adjDots[nr][nc] == 1) {
                    frontier.push_back({nr, nc});
                }
            }
        }
    };

    // Choose random starting cell
    int sr = rnd.next(0, R - 1);
    int sc = rnd.next(0, C - 1);
    grid[sr][sc] = '.';
    int totalFree = 1;
    addNeighbor(sr, sc);

    int capacity = R * C;
    int treeType = rnd.next(0, 3); // 0..3

    int minNodes, maxNodes;
    if (treeType == 0) {
        // Single dot case
        minNodes = 1;
        maxNodes = 1;
    } else if (treeType == 1) {
        minNodes = 2;
        maxNodes = max(2, capacity / 4);
    } else if (treeType == 2) {
        minNodes = max(2, capacity / 4);
        maxNodes = max(minNodes, capacity / 2);
    } else {
        minNodes = max(2, capacity / 2);
        maxNodes = max(minNodes, (capacity * 2) / 3);
    }
    int targetNodes = rnd.next(minNodes, maxNodes);

    static const int dr[4] = {-1, 1, 0, 0};
    static const int dc[4] = {0, 0, -1, 1};

    while (!frontier.empty() && totalFree < targetNodes) {
        int id = rnd.next(0, (int)frontier.size() - 1);
        auto cell = frontier[id];
        frontier[id] = frontier.back();
        frontier.pop_back();

        int r = cell.first;
        int c = cell.second;
        if (grid[r][c] == '.') continue;
        if (adjDots[r][c] != 1) continue;

        grid[r][c] = '.';
        totalFree++;
        addNeighbor(r, c);
    }

    return grid;
}

vector<string> buildLineLabyrinth(int R, int C) {
    vector<string> grid(R, string(C, '#'));
    int orientation = rnd.next(0, 1); // 0 horizontal, 1 vertical

    if (orientation == 0) {
        int r = rnd.next(0, R - 1);
        int len = rnd.next(1, C);
        int startc = rnd.next(0, C - len);
        for (int j = startc; j < startc + len; ++j)
            grid[r][j] = '.';
    } else {
        int c = rnd.next(0, C - 1);
        int len = rnd.next(1, R);
        int startr = rnd.next(0, R - len);
        for (int i = startr; i < startr + len; ++i)
            grid[i][c] = '.';
    }

    return grid;
}

vector<string> buildPlusLabyrinth(int R, int C) {
    vector<string> grid(R, string(C, '#'));

    int rCenter = rnd.next(1, R - 2);
    int cCenter = rnd.next(1, C - 2);
    grid[rCenter][cCenter] = '.';

    int lenU = rnd.next(1, rCenter);
    int lenD = rnd.next(1, R - 1 - rCenter);
    int lenL = rnd.next(1, cCenter);
    int lenR = rnd.next(1, C - 1 - cCenter);

    for (int k = 1; k <= lenU; ++k)
        grid[rCenter - k][cCenter] = '.';
    for (int k = 1; k <= lenD; ++k)
        grid[rCenter + k][cCenter] = '.';
    for (int k = 1; k <= lenL; ++k)
        grid[rCenter][cCenter - k] = '.';
    for (int k = 1; k <= lenR; ++k)
        grid[rCenter][cCenter + k] = '.';

    return grid;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // With some probability, emit the exact sample from the statement
    if (rnd.next(0, 9) == 0) {
        printSample();
        return 0;
    }

    int T = rnd.next(1, 2);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int sizeType = rnd.next(0, 2); // 0,1,2
        int R, C;

        if (sizeType == 0) {
            R = rnd.next(3, 7);
            C = rnd.next(3, 7);
        } else if (sizeType == 1) {
            if (rnd.next(0, 1) == 0) {
                R = rnd.next(3, 5);
                C = rnd.next(8, 15);
            } else {
                R = rnd.next(8, 15);
                C = rnd.next(3, 5);
            }
        } else {
            R = rnd.next(8, 15);
            C = rnd.next(8, 15);
        }

        int shapeType = rnd.next(0, 2); // 0: random tree, 1: line, 2: plus (if possible)
        vector<string> grid;

        if (shapeType == 1) {
            grid = buildLineLabyrinth(R, C);
        } else if (shapeType == 2 && R >= 3 && C >= 3) {
            grid = buildPlusLabyrinth(R, C);
        } else {
            grid = buildRandomTreeLabyrinth(R, C);
        }

        // Output: C columns first, then R rows
        println(C, R);
        for (int i = 0; i < R; ++i) {
            printf("%s\n", grid[i].c_str());
        }
    }

    return 0;
}
