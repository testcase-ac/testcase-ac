#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

const string FIRST = "EI";
const string SECOND = "NS";
const string THIRD = "TF";
const string FOURTH = "JP";
const string ALL_UPPER = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const vector<pair<int, int>> DIRS = {
    {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1},
};

string randomMbti() {
    string s;
    s += rnd.any(FIRST);
    s += rnd.any(SECOND);
    s += rnd.any(THIRD);
    s += rnd.any(FOURTH);
    return s;
}

bool fits(int r, int c, int dr, int dc, int n, int m) {
    int er = r + 3 * dr;
    int ec = c + 3 * dc;
    return 0 <= er && er < n && 0 <= ec && ec < m;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n, m;
    if (mode == 0) {
        n = rnd.next(1, 3);
        m = rnd.next(1, 3);
    } else if (mode == 1) {
        n = rnd.next(1, 2) == 1 ? 1 : rnd.next(4, 10);
        m = n == 1 ? rnd.next(4, 12) : 1;
    } else if (mode == 2) {
        n = rnd.next(4, 10);
        m = rnd.next(4, 10);
    } else {
        n = rnd.next(4, 12);
        m = rnd.next(4, 12);
    }

    string alphabet = ALL_UPPER;
    if (mode == 3) alphabet = FIRST + SECOND + THIRD + FOURTH;
    if (mode == 4) alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZENSFTJP";

    vector<string> board(n, string(m, 'A'));
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            board[r][c] = rnd.any(alphabet);
        }
    }

    if (mode != 0) {
        int placements = rnd.next(1, min(10, max(1, n * m / 3)));
        for (int attempt = 0; attempt < placements * 20 && placements > 0; ++attempt) {
            int r = rnd.next(0, n - 1);
            int c = rnd.next(0, m - 1);
            auto dir = rnd.any(DIRS);
            if (!fits(r, c, dir.first, dir.second, n, m)) continue;

            string word = randomMbti();
            if (rnd.next(0, 1)) reverse(word.begin(), word.end());
            for (int k = 0; k < 4; ++k) {
                board[r + k * dir.first][c + k * dir.second] = word[k];
            }
            --placements;
        }
    }

    println(n, m);
    for (const string& row : board) println(row);

    return 0;
}
