#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

vector<int> distinctInts(int count, int lo, int hi) {
    set<int> seen;
    while ((int)seen.size() < count) {
        seen.insert(rnd.next(lo, hi));
    }
    return vector<int>(seen.begin(), seen.end());
}

vector<int> arithmeticInts(int count, int start, int step) {
    vector<int> values;
    values.reserve(count);
    for (int i = 0; i < count; ++i) {
        values.push_back(start + i * step);
    }
    return values;
}

void maybeShuffle(vector<int>& values) {
    if (rnd.next(0, 1) == 1) {
        shuffle(values.begin(), values.end());
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;
    int y1;
    int y2;
    vector<int> top;
    vector<int> bottom;

    if (mode == 0) {
        n = rnd.next(2, 8);
        m = rnd.next(2, 8);
        y1 = rnd.next(-10, 10);
        do {
            y2 = rnd.next(-10, 10);
        } while (y1 == y2);
        top = distinctInts(n, -12, 12);
        bottom = distinctInts(m, -12, 12);
    } else if (mode == 1) {
        n = rnd.next(2, 7);
        m = rnd.next(2, 7);
        y1 = rnd.next(-100, 100);
        y2 = y1 + rnd.any(vector<int>{-7, -1, 1, 7});
        top = arithmeticInts(n, -n + rnd.next(-3, 3), rnd.next(1, 3));
        bottom = arithmeticInts(m, -m + rnd.next(-3, 3), rnd.next(1, 3));
    } else if (mode == 2) {
        n = rnd.next(2, 9);
        m = rnd.next(2, 9);
        y1 = -1000000000;
        y2 = 1000000000;
        top = distinctInts(n, -1000000000, -999999980);
        bottom = distinctInts(m, 999999980, 1000000000);
    } else if (mode == 3) {
        n = rnd.next(2, 10);
        m = rnd.next(2, 10);
        y1 = rnd.next(-1000, 1000);
        y2 = y1 + rnd.any(vector<int>{-1000, -2, 2, 1000});
        int common = rnd.next(-5, 5);
        top = distinctInts(n, -20, 20);
        bottom = distinctInts(m, -20, 20);
        top[0] = common;
        bottom[0] = common;
        sort(top.begin(), top.end());
        top.erase(unique(top.begin(), top.end()), top.end());
        while ((int)top.size() < n) {
            int x = rnd.next(-20, 20);
            if (find(top.begin(), top.end(), x) == top.end()) {
                top.push_back(x);
            }
        }
        sort(bottom.begin(), bottom.end());
        bottom.erase(unique(bottom.begin(), bottom.end()), bottom.end());
        while ((int)bottom.size() < m) {
            int x = rnd.next(-20, 20);
            if (find(bottom.begin(), bottom.end(), x) == bottom.end()) {
                bottom.push_back(x);
            }
        }
    } else if (mode == 4) {
        n = rnd.next(2, 4);
        m = rnd.next(12, 30);
        y1 = rnd.next(-1000000, 1000000);
        y2 = rnd.next(-1000000, 1000000);
        if (y1 == y2) {
            ++y2;
        }
        top = distinctInts(n, -50, 50);
        bottom = distinctInts(m, -200, 200);
    } else {
        n = rnd.next(12, 30);
        m = rnd.next(2, 4);
        y1 = rnd.next(-1000000, 1000000);
        y2 = rnd.next(-1000000, 1000000);
        if (y1 == y2) {
            --y2;
        }
        top = distinctInts(n, -200, 200);
        bottom = distinctInts(m, -50, 50);
    }

    maybeShuffle(top);
    maybeShuffle(bottom);

    println(n, m, y1, y2);
    for (int x : top) {
        println(x);
    }
    for (int x : bottom) {
        println(x);
    }

    return 0;
}
