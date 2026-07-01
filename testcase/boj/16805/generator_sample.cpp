#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string noisyBoundaryRow(int n, int boundary, int noisePercent) {
    string row;
    row.reserve(n);
    for (int j = 1; j <= n; ++j) {
        char expected = (j <= boundary ? 'W' : 'E');
        if (rnd.next(1, 100) <= noisePercent) {
            expected = (expected == 'W' ? 'E' : 'W');
        }
        row.push_back(expected);
    }
    return row;
}

string randomRow(int n, int westPercent) {
    string row;
    row.reserve(n);
    for (int j = 0; j < n; ++j) {
        row.push_back(rnd.next(1, 100) <= westPercent ? 'W' : 'E');
    }
    return row;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    int m = rnd.next(1, 12);
    vector<string> rows;
    rows.reserve(m);

    if (mode == 0) {
        int boundary = rnd.next(0, n);
        int noisePercent = rnd.next(0, 15);
        for (int i = 0; i < m; ++i) {
            rows.push_back(noisyBoundaryRow(n, boundary, noisePercent));
        }
    } else if (mode == 1) {
        char fill = rnd.next(0, 1) == 0 ? 'E' : 'W';
        for (int i = 0; i < m; ++i) {
            string row(n, fill);
            int flips = rnd.next(0, max(0, n / 6));
            for (int k = 0; k < flips; ++k) {
                int pos = rnd.next(0, n - 1);
                row[pos] = (row[pos] == 'W' ? 'E' : 'W');
            }
            rows.push_back(row);
        }
    } else if (mode == 2) {
        int westPercent = rnd.next(10, 90);
        for (int i = 0; i < m; ++i) {
            rows.push_back(randomRow(n, westPercent));
        }
    } else if (mode == 3) {
        for (int i = 0; i < m; ++i) {
            string row;
            row.reserve(n);
            int offset = rnd.next(0, 1);
            for (int j = 0; j < n; ++j) {
                row.push_back((j + offset) % 2 == 0 ? 'W' : 'E');
            }
            rows.push_back(row);
        }
    } else if (mode == 4) {
        int left = rnd.next(0, n);
        int right = rnd.next(left, n);
        for (int i = 0; i < m; ++i) {
            string row;
            row.reserve(n);
            for (int j = 1; j <= n; ++j) {
                if (j <= left) {
                    row.push_back('W');
                } else if (j > right) {
                    row.push_back('E');
                } else {
                    row.push_back(rnd.next(0, 1) == 0 ? 'W' : 'E');
                }
            }
            rows.push_back(row);
        }
    } else {
        n = rnd.any(vector<int>{1, 2, 3, 4, 5, 10, 30});
        m = rnd.any(vector<int>{1, 2, 3, 10, 12});
        for (int i = 0; i < m; ++i) {
            int boundary = rnd.next(0, n);
            rows.push_back(noisyBoundaryRow(n, boundary, rnd.next(0, 30)));
        }
    }

    println(n, m);
    for (const string& row : rows) {
        println(row);
    }

    return 0;
}
