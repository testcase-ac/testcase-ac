#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

char pickChar(const string& alphabet) {
    return alphabet[rnd.next((int)alphabet.size())];
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = 1;
    int m = 1;

    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 24);
    } else if (mode == 1) {
        n = rnd.next(1, 24);
        m = 1;
    } else {
        n = rnd.next(2, 14);
        m = rnd.next(2, 14);
    }

    vector<string> grid(n, string(m, 'E'));
    string alphabet = "ESM";

    if (mode == 0 || mode == 1) {
        string pattern = rnd.any(vector<string>{"ESM", "EMS", "SEMMSE", "EEE", "SSS", "MMM"});
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int offset = rnd.next(0, (int)pattern.size() - 1);
                grid[i][j] = pattern[(i + j + offset) % (int)pattern.size()];
            }
        }
    } else if (mode == 2) {
        char fill = pickChar(alphabet);
        for (int i = 0; i < n; ++i) {
            fill_n(grid[i].begin(), m, fill);
        }
        int changes = rnd.next(1, max(1, min(n * m, 12)));
        for (int t = 0; t < changes; ++t) {
            grid[rnd.next(n)][rnd.next(m)] = pickChar(alphabet);
        }
    } else if (mode == 3) {
        int rowSplit = rnd.next(1, n - 1);
        int colSplit = rnd.next(1, m - 1);
        vector<char> chars = {'E', 'S', 'M'};
        shuffle(chars.begin(), chars.end());
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int region = (i >= rowSplit) + (j >= colSplit);
                grid[i][j] = chars[min(region, 2)];
            }
        }
    } else if (mode == 4) {
        int shift = rnd.next(0, 2);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int band = (i + j + shift) % 3;
                grid[i][j] = alphabet[band];
            }
        }
    } else {
        vector<int> weights = {rnd.next(1, 6), rnd.next(1, 6), rnd.next(1, 6)};
        int total = weights[0] + weights[1] + weights[2];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int x = rnd.next(1, total);
                if (x <= weights[0]) {
                    grid[i][j] = 'E';
                } else if (x <= weights[0] + weights[1]) {
                    grid[i][j] = 'S';
                } else {
                    grid[i][j] = 'M';
                }
            }
        }
    }

    println(n, m);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
