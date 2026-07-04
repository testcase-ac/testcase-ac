#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

static vector<int> randomValues(int count, int lo, int hi) {
    vector<int> values(count);
    for (int& value : values) value = rnd.next(lo, hi);
    return values;
}

static vector<int> beautyValues(int m, int l, int mode) {
    vector<int> s(m);

    if (mode == 0) {
        int value = rnd.next(1, min(100000, max(1, l / 3 + 1)));
        fill(s.begin(), s.end(), value);
    } else if (mode == 1) {
        for (int i = 0; i < m; ++i) {
            int delta = rnd.next(-3, 3);
            s[i] = max(1, min(100000, l + delta));
        }
    } else if (mode == 2) {
        for (int i = 0; i < m; ++i) {
            s[i] = (i % 2 == 0) ? rnd.next(1, 5) : rnd.next(max(1, l - 5), min(100000, l + 5));
        }
    } else {
        int lo = rnd.next(1, min(100000, max(1, l)));
        int hi = rnd.next(lo, min(100000, max(lo, l * 2)));
        for (int& value : s) value = rnd.next(lo, hi);
    }

    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(3, 20);
    int m = rnd.next(1, 40);
    int l = rnd.any(vector<int>{1, 2, 3, 10, 99, 100000, rnd.next(1, 100000)});
    vector<int> k;

    if (mode == 0) {
        m = rnd.next(1, 8);
        n = rnd.next(3, 16);
        k.assign(n, rnd.next(1, m));
    } else if (mode == 1) {
        m = rnd.next(3, 30);
        n = rnd.next(3, 24);
        int center = rnd.next(1, m);
        int radius = rnd.next(0, min(4, max(center - 1, m - center)));
        int lo = max(1, center - radius);
        int hi = min(m, center + radius);
        k = randomValues(n, lo, hi);
    } else if (mode == 2) {
        m = rnd.next(2, 50);
        n = rnd.next(3, 25);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                k.push_back(rnd.next(1, m));
            } else {
                k.push_back(rnd.next(0, 1) ? 1 : m);
            }
        }
    } else if (mode == 3) {
        m = rnd.next(2, 35);
        int distinct = rnd.next(2, min(m, 8));
        n = rnd.next(max(3, distinct), 35);
        vector<int> pitches;
        while ((int)pitches.size() < distinct) {
            int value = rnd.next(1, m);
            if (find(pitches.begin(), pitches.end(), value) == pitches.end()) pitches.push_back(value);
        }
        for (int i = 0; i < n; ++i) k.push_back(rnd.any(pitches));
        shuffle(k.begin(), k.end());
    } else if (mode == 4) {
        m = rnd.next(5, 60);
        n = rnd.next(12, 45);
        int step = rnd.next(1, max(1, m / 6));
        int start = rnd.next(1, step);
        for (int i = 0; i < n; ++i) {
            int value = start + step * rnd.next(0, (m - start) / step);
            k.push_back(min(m, value));
        }
    } else {
        m = rnd.next(1, 80);
        n = rnd.next(30, 80);
        k = randomValues(n, 1, m);
    }

    vector<int> s = beautyValues(m, l, rnd.next(0, 3));

    println(n, m, l);
    println(k);
    println(s);

    return 0;
}
