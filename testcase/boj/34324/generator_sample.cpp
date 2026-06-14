#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

const string ALPHABET = "KUMOH";
const string TARGET = "KUMOH";
const string REVERSE_TARGET = "HOMUK";

void placePattern(vector<string>& grid, int row, int col, const string& pattern) {
    for (int i = 0; i < (int)pattern.size(); ++i) {
        grid[row - i][col + i] = pattern[i];
    }
}

bool canPlace(const vector<string>& grid, int row, int col) {
    if (row < 4) return false;
    for (int i = 0; i < 5; ++i) {
        int r = row - i;
        int c = col + i;
        if (c < 0 || c >= (int)grid[r].size()) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int maxLen;

    if (mode == 0) {
        n = rnd.next(1, 4);
        maxLen = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(5, 9);
        maxLen = rnd.next(5, 12);
    } else if (mode == 2) {
        n = rnd.next(8, 18);
        maxLen = rnd.next(8, 25);
    } else if (mode == 3) {
        n = rnd.next(5, 15);
        maxLen = rnd.next(5, 20);
    } else {
        n = rnd.next(15, 30);
        maxLen = rnd.next(20, 45);
    }

    vector<string> grid(n);
    for (int r = 0; r < n; ++r) {
        int len;
        if (mode == 3) {
            len = rnd.next(1, maxLen);
        } else {
            int low = max(1, maxLen - rnd.next(0, min(maxLen - 1, 5)));
            len = rnd.next(low, maxLen);
        }

        grid[r].reserve(len);
        for (int c = 0; c < len; ++c) {
            grid[r].push_back(rnd.any(ALPHABET));
        }
    }

    vector<pair<int, int>> starts;
    for (int r = 4; r < n; ++r) {
        for (int c = 0; c < (int)grid[r].size(); ++c) {
            if (canPlace(grid, r, c)) starts.push_back({r, c});
        }
    }
    shuffle(starts.begin(), starts.end());

    if (!starts.empty() && mode != 0) {
        int placements = min((int)starts.size(), rnd.next(1, min(8, (int)starts.size())));
        for (int i = 0; i < placements; ++i) {
            const string& pattern = rnd.next(0, 1) == 0 ? TARGET : REVERSE_TARGET;
            placePattern(grid, starts[i].first, starts[i].second, pattern);
        }
    }

    if (mode == 4 && n >= 5) {
        for (int offset = 0; offset + 4 < min((int)grid[n - 1].size(), 12); offset += 5) {
            if (canPlace(grid, n - 1, offset)) {
                placePattern(grid, n - 1, offset, TARGET);
            }
        }
    }

    println(n);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
