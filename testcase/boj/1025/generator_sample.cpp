#include "testlib.h"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 9);
    int m = rnd.next(1, 9);
    int mode = rnd.next(0, 4);
    vector<string> grid(n, string(m, '0'));

    if (mode == 0) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                grid[i][j] = char('0' + rnd.next(0, 9));
    } else if (mode == 1) {
        string digits = rnd.next(0, 1) ? "01346789" : "2357";
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                grid[i][j] = rnd.any(digits);
    } else if (mode == 2) {
        int start = rnd.next(0, 9);
        int rowStep = rnd.next(0, 9);
        int colStep = rnd.next(0, 9);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                grid[i][j] = char('0' + (start + i * rowStep + j * colStep) % 10);
    } else {
        char fill = rnd.any(string("0000013579"));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                grid[i][j] = fill;
        int changes = rnd.next(1, n * m);
        for (int k = 0; k < changes; ++k)
            grid[rnd.next(0, n - 1)][rnd.next(0, m - 1)] = char('0' + rnd.next(0, 9));
    }

    if (mode == 4 || rnd.next(0, 2) == 0) {
        int r0 = rnd.next(0, n - 1);
        int c0 = rnd.next(0, m - 1);
        vector<pair<int, int>> deltas;
        for (int dr = -8; dr <= 8; ++dr) {
            for (int dc = -8; dc <= 8; ++dc) {
                if (dr == 0 && dc == 0) continue;
                int len = 0;
                int r = r0;
                int c = c0;
                while (0 <= r && r < n && 0 <= c && c < m) {
                    ++len;
                    r += dr;
                    c += dc;
                }
                if (len >= 2) deltas.push_back({dr, dc});
            }
        }

        if (!deltas.empty()) {
            pair<int, int> delta = rnd.any(deltas);
            int maxLen = 0;
            int r = r0;
            int c = c0;
            while (0 <= r && r < n && 0 <= c && c < m) {
                ++maxLen;
                r += delta.first;
                c += delta.second;
            }
            int len = rnd.next(1, maxLen);
            int upper = 1;
            for (int i = 0; i < len; ++i) upper *= 10;
            int root = rnd.next(0, max(0, int(sqrt(upper - 1))));
            string square = to_string(root * root);
            if ((int)square.size() > len) square = square.substr(0, len);
            while ((int)square.size() < len) square = "0" + square;

            r = r0;
            c = c0;
            for (char ch : square) {
                grid[r][c] = ch;
                r += delta.first;
                c += delta.second;
            }
        }
    }

    println(n, m);
    for (const string& row : grid) println(row);
    return 0;
}
