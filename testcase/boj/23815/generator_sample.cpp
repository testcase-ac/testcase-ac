#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

static string op(char kind, int x) {
    return string(1, kind) + char('0' + x);
}

static string randomOp(const string& kinds, int lo = 1, int hi = 9) {
    return op(rnd.any(kinds), rnd.next(lo, hi));
}

static void addRandomRows(vector<pair<string, string>>& rows, int count,
                          const string& kinds) {
    for (int i = 0; i < count; ++i) {
        rows.push_back({randomOp(kinds), randomOp(kinds)});
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<string, string>> rows;
    int mode = rnd.next(0, 6);

    if (mode == 0) {
        int n = rnd.next(1, 25);
        addRandomRows(rows, n, "+-*/");
    } else if (mode == 1) {
        int n = rnd.next(3, 18);
        addRandomRows(rows, rnd.next(1, 4), "+*");
        rows.push_back({op('-', rnd.next(7, 9)), op('/', rnd.next(2, 9))});
        addRandomRows(rows, n - (int)rows.size(), "+-*/");
        shuffle(rows.begin(), rows.end());
    } else if (mode == 2) {
        int n = rnd.next(2, 16);
        addRandomRows(rows, rnd.next(1, 3), "+*");
        for (int i = rows.size(); i < n; ++i) {
            rows.push_back({op('-', rnd.next(1, 9)), op('-', rnd.next(1, 9))});
        }
    } else if (mode == 3) {
        int n = rnd.next(1, 24);
        for (int i = 0; i < n; ++i) {
            string cur = randomOp("+-*/");
            if (rnd.next(0, 2) == 0) {
                rows.push_back({cur, cur});
            } else {
                rows.push_back({cur, randomOp("+-*/")});
            }
        }
    } else if (mode == 4) {
        int n = rnd.next(5, 30);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                rows.push_back({op('+', rnd.next(1, 9)), op('*', rnd.next(1, 3))});
            } else {
                rows.push_back({op('/', rnd.next(1, 9)), op('-', rnd.next(1, 4))});
            }
        }
    } else if (mode == 5) {
        int n = rnd.next(20, 60);
        for (int i = 0; i < n; ++i) {
            rows.push_back({op('+', rnd.next(1, 9)), op('-', rnd.next(1, 9))});
        }
    } else {
        int n = rnd.next(8, 35);
        for (int i = 0; i < n; ++i) {
            if (i % 4 == 0) rows.push_back({op('*', rnd.next(1, 3)), op('+', rnd.next(1, 9))});
            else if (i % 4 == 1) rows.push_back({op('/', rnd.next(1, 9)), op('+', rnd.next(1, 5))});
            else if (i % 4 == 2) rows.push_back({op('-', rnd.next(1, 9)), op('*', rnd.next(1, 2))});
            else rows.push_back({randomOp("+-*/"), randomOp("+-*/")});
        }
    }

    println((int)rows.size());
    for (const auto& row : rows) {
        println(row.first, row.second);
    }

    return 0;
}
