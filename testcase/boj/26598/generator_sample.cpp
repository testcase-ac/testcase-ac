#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

char letter(int x) {
    return char('A' + (x % 26));
}

void printGrid(const vector<string>& grid) {
    println((int)grid.size(), (int)grid[0].size());
    for (const string& row : grid) println(row);
}

vector<int> randomCuts(int length, int maxParts) {
    vector<int> cuts;
    int parts = rnd.next(1, min(length, maxParts));
    for (int i = 1; i < length; ++i) cuts.push_back(i);
    shuffle(cuts.begin(), cuts.end());
    cuts.resize(parts - 1);
    sort(cuts.begin(), cuts.end());
    cuts.push_back(length);
    return cuts;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 12);
    int m = rnd.next(1, 18);
    vector<string> grid(n, string(m, 'A'));

    if (mode == 0) {
        vector<int> rowCuts = randomCuts(n, 5);
        vector<int> colCuts = randomCuts(m, 6);
        int prevR = 0;
        int color = rnd.next(0, 25);
        for (int rCut : rowCuts) {
            int prevC = 0;
            for (int cCut : colCuts) {
                char c = letter(color++);
                for (int r = prevR; r < rCut; ++r) {
                    for (int col = prevC; col < cCut; ++col) grid[r][col] = c;
                }
                prevC = cCut;
            }
            prevR = rCut;
        }
    } else if (mode == 1) {
        bool vertical = rnd.next(0, 1);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                int band = vertical ? c : r;
                grid[r][c] = letter(band + rnd.next(0, 3));
            }
        }
    } else if (mode == 2) {
        char outer = letter(rnd.next(0, 25));
        char inner = letter(rnd.next(0, 25));
        if (inner == outer) inner = letter(inner - 'A' + 1);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) grid[r][c] = outer;
        }
        if (n >= 3 && m >= 3) {
            int top = rnd.next(1, n - 2);
            int left = rnd.next(1, m - 2);
            int bottom = rnd.next(top, n - 2);
            int right = rnd.next(left, m - 2);
            for (int r = top; r <= bottom; ++r) {
                for (int c = left; c <= right; ++c) grid[r][c] = inner;
            }
        }
    } else if (mode == 3) {
        char c1 = letter(rnd.next(0, 25));
        char c2 = letter(rnd.next(0, 25));
        if (c1 == c2) c2 = letter(c2 - 'A' + 1);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) grid[r][c] = ((r + c) % 2 == 0 ? c1 : c2);
        }
    } else if (mode == 4) {
        int colors = rnd.next(2, 8);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) grid[r][c] = letter(rnd.next(0, colors - 1));
        }
    } else {
        vector<int> rowCuts = randomCuts(n, 4);
        int prevR = 0;
        for (int rCut : rowCuts) {
            char c = letter(rnd.next(0, 25));
            for (int r = prevR; r < rCut; ++r) {
                for (int col = 0; col < m; ++col) grid[r][col] = c;
            }
            prevR = rCut;
        }
        for (int tweaks = rnd.next(1, max(1, n * m / 8)); tweaks > 0; --tweaks) {
            grid[rnd.next(0, n - 1)][rnd.next(0, m - 1)] = letter(rnd.next(0, 25));
        }
    }

    printGrid(grid);
    return 0;
}
