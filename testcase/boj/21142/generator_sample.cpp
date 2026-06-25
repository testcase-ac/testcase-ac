#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string alphabetPrefix(int k) {
    string s;
    for (int i = 0; i < k; ++i) {
        s.push_back(static_cast<char>('A' + i));
    }
    return s;
}

string rotated(string s, int shift) {
    if (s.empty()) {
        return s;
    }
    shift %= static_cast<int>(s.size());
    rotate(s.begin(), s.begin() + shift, s.end());
    return s;
}

string withRandomSwaps(string s, int swaps) {
    int k = static_cast<int>(s.size());
    for (int i = 0; i < swaps; ++i) {
        int a = rnd.next(0, k - 1);
        int b = rnd.next(0, k - 1);
        swap(s[a], s[b]);
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int k;
    int n;

    if (mode == 0) {
        k = rnd.next(1, 4);
        n = rnd.next(1, 5);
    } else if (mode == 1) {
        k = rnd.next(2, 10);
        n = rnd.next(2, 8);
    } else if (mode == 2) {
        k = rnd.next(5, 16);
        n = rnd.next(2, 10);
    } else if (mode == 3) {
        k = rnd.next(8, 26);
        n = rnd.next(2, 6);
    } else if (mode == 4) {
        k = rnd.next(2, 12);
        n = rnd.next(8, 20);
    } else {
        k = rnd.next(1, 26);
        n = rnd.next(1, 20);
    }

    string base = alphabetPrefix(k);
    vector<string> rows;
    rows.reserve(n);

    if (mode == 0) {
        shuffle(base.begin(), base.end());
        for (int i = 0; i < n; ++i) {
            rows.push_back(base);
        }
    } else if (mode == 1) {
        string reverseBase = base;
        reverse(reverseBase.begin(), reverseBase.end());
        for (int i = 0; i < n; ++i) {
            rows.push_back((i % 2 == 0) ? base : reverseBase);
        }
    } else if (mode == 2) {
        shuffle(base.begin(), base.end());
        for (int i = 0; i < n; ++i) {
            rows.push_back(rotated(base, rnd.next(0, k - 1)));
        }
    } else if (mode == 3) {
        shuffle(base.begin(), base.end());
        int maxSwaps = rnd.next(1, max(1, k / 2));
        for (int i = 0; i < n; ++i) {
            rows.push_back(withRandomSwaps(base, rnd.next(1, maxSwaps)));
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            string s = base;
            shuffle(s.begin(), s.end());
            rows.push_back(s);
        }
    } else {
        shuffle(base.begin(), base.end());
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 2) == 0) {
                rows.push_back(base);
            } else if (rnd.next(0, 1) == 0) {
                rows.push_back(rotated(base, rnd.next(0, k - 1)));
            } else {
                rows.push_back(withRandomSwaps(base, rnd.next(1, max(1, k / 3))));
            }
        }
    }

    shuffle(rows.begin(), rows.end());

    println(n, k);
    for (const string& row : rows) {
        println(row);
    }

    return 0;
}
