#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

static string repeatChar(char c, int len) {
    return string(len, c);
}

static string alternatingRow(int len, char first) {
    string row;
    row.reserve(len);
    for (int i = 0; i < len; ++i) {
        row.push_back((i % 2 == 0) == (first == 'B') ? 'B' : 'G');
    }
    return row;
}

static string randomRow(int len, int boyPercent) {
    string row;
    row.reserve(len);
    for (int i = 0; i < len; ++i) {
        row.push_back(rnd.next(1, 100) <= boyPercent ? 'B' : 'G');
    }
    return row;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, mode == 5 ? 40 : 14);
    vector<string> rows;
    rows.reserve(n);

    for (int i = 0; i < n; ++i) {
        int len = 1;
        if (mode == 0) {
            len = rnd.next(1, 5);
            rows.push_back(randomRow(len, rnd.any(vector<int>{0, 25, 50, 75, 100})));
        } else if (mode == 1) {
            len = rnd.next(1, 15);
            rows.push_back(alternatingRow(len, rnd.any(string("BG"))));
        } else if (mode == 2) {
            len = rnd.next(1, 20);
            rows.push_back(repeatChar(rnd.any(string("BG")), len));
        } else if (mode == 3) {
            len = rnd.next(1, 2 * rnd.next(1, 12) - 1);
            if (rnd.next(0, 1) == 0) ++len;
            rows.push_back(randomRow(len, rnd.next(10, 90)));
        } else if (mode == 4) {
            len = rnd.next(1, 100);
            int boyPercent = rnd.any(vector<int>{5, 35, 50, 65, 95});
            rows.push_back(randomRow(len, boyPercent));
        } else {
            len = rnd.next(1, 100);
            if (i % 3 == 0) {
                rows.push_back(alternatingRow(len, rnd.any(string("BG"))));
            } else if (i % 3 == 1) {
                rows.push_back(repeatChar(rnd.any(string("BG")), len));
            } else {
                rows.push_back(randomRow(len, rnd.next(20, 80)));
            }
        }
    }

    shuffle(rows.begin(), rows.end());

    println(n);
    for (const string& row : rows) {
        println(row);
    }

    return 0;
}
