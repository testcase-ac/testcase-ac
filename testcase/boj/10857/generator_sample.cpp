#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

vector<int> randomRow(int x, int y, int mode) {
    vector<int> row(x);
    if (mode == 0) {
        int value = rnd.next(0, y);
        fill(row.begin(), row.end(), value);
    } else if (mode == 1) {
        int lo = rnd.next(0, y);
        int hi = rnd.next(lo, y);
        for (int& value : row) value = rnd.next(lo, hi);
    } else if (mode == 2) {
        for (int i = 0; i < x; ++i) row[i] = (i % 2 == 0 ? 0 : y);
    } else if (mode == 3) {
        int current = rnd.next(0, y);
        for (int i = 0; i < x; ++i) {
            current += rnd.next(-3, 3);
            current = max(0, min(y, current));
            row[i] = current;
        }
    } else {
        for (int& value : row) value = rnd.next(0, y);
    }
    return row;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int x = rnd.next(1, 12);
    int y = rnd.next(1, 30);
    int w = rnd.next(1, mode == 5 ? 12 : 6);
    int s = rnd.next(1, mode == 5 ? 20 : 8);

    if (mode == 0) {
        x = 1;
        y = rnd.next(1, 10);
    } else if (mode == 1) {
        y = rnd.any(vector<int>{1, 2, 100});
    } else if (mode == 2) {
        x = rnd.next(8, 15);
        y = rnd.next(20, 100);
    }

    println(w, s);
    println(x, y);

    for (int i = 0; i < w; ++i) {
        println(randomRow(x, y, rnd.next(0, 4)));
    }

    for (int i = 0; i < s; ++i) {
        vector<int> cut = randomRow(x, y, rnd.next(0, 4));
        if (i == 0 && rnd.next(0, 1) == 1) {
            int column = rnd.next(0, x - 1);
            cut[column] = y;
        }
        println(cut);
    }

    return 0;
}
