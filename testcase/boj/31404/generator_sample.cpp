#include "testlib.h"
#include <string>
#include <vector>

using namespace std;

string randomRow(int w, int lo = 0, int hi = 3) {
    string row;
    row.reserve(w);
    for (int c = 0; c < w; ++c) {
        row.push_back(char('0' + rnd.next(lo, hi)));
    }
    return row;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int h, w;

    if (mode == 0) {
        h = 1;
        w = rnd.next(1, 12);
    } else if (mode == 1) {
        h = rnd.next(1, 12);
        w = 1;
    } else if (mode == 2) {
        h = rnd.next(2, 5);
        w = rnd.next(2, 5);
    } else if (mode == 3) {
        h = rnd.next(6, 10);
        w = rnd.next(2, 8);
    } else if (mode == 4) {
        h = rnd.next(2, 8);
        w = rnd.next(6, 10);
    } else {
        h = rnd.next(8, 12);
        w = rnd.next(8, 12);
    }

    int r, c;
    if (rnd.next(0, 99) < 45) {
        r = rnd.any(vector<int>{0, h - 1});
        c = rnd.next(0, w - 1);
    } else if (rnd.next(0, 99) < 70) {
        r = rnd.next(0, h - 1);
        c = rnd.any(vector<int>{0, w - 1});
    } else {
        r = rnd.next(0, h - 1);
        c = rnd.next(0, w - 1);
    }
    int d = rnd.next(0, 3);

    vector<string> a(h), b(h);
    if (mode == 0 || mode == 1) {
        for (int i = 0; i < h; ++i) {
            a[i] = randomRow(w);
            b[i] = randomRow(w);
        }
    } else if (mode == 2) {
        int turnA = rnd.next(0, 3);
        int turnB = rnd.next(0, 3);
        for (int i = 0; i < h; ++i) {
            a[i] = string(w, char('0' + turnA));
            b[i] = string(w, char('0' + turnB));
        }
    } else if (mode == 3) {
        for (int i = 0; i < h; ++i) {
            a[i].reserve(w);
            b[i].reserve(w);
            for (int j = 0; j < w; ++j) {
                a[i].push_back(char('0' + ((i + j + rnd.next(0, 1)) % 4)));
                b[i].push_back(char('0' + ((2 * i + j + rnd.next(0, 1)) % 4)));
            }
        }
    } else if (mode == 4) {
        for (int i = 0; i < h; ++i) {
            a[i] = randomRow(w, 0, 1);
            b[i] = randomRow(w, 2, 3);
        }
    } else {
        for (int i = 0; i < h; ++i) {
            a[i] = randomRow(w);
            b[i] = randomRow(w);
        }
    }

    println(h, w);
    println(r, c, d);
    for (const string& row : a) {
        println(row);
    }
    for (const string& row : b) {
        println(row);
    }

    return 0;
}
