#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

static vector<int> makeByGaps(int h, int minGap, int maxGap) {
    int total = 0;
    vector<int> gaps(h - 1);
    for (int i = 0; i + 1 < h; ++i) {
        gaps[i] = rnd.next(minGap, maxGap);
        total += gaps[i];
    }

    int start = rnd.next(0, 1000000 - total);
    vector<int> x(h);
    x[0] = start;
    for (int i = 1; i < h; ++i) {
        x[i] = x[i - 1] + gaps[i - 1];
    }
    return x;
}

static vector<int> makePicked(int h, const vector<int>& pool) {
    vector<int> values = pool;
    shuffle(values.begin(), values.end());
    values.resize(h);
    sort(values.begin(), values.end());
    return values;
}

static vector<int> makeCase(int h, int mode) {
    if (mode == 0) {
        return makeByGaps(h, 1, rnd.next(1, 6));
    }

    if (mode == 1) {
        int maxGap = min(80000, 1000000 / (h - 1));
        int minGap = min(rnd.next(2000, 10000), maxGap);
        return makeByGaps(h, minGap, maxGap);
    }

    if (mode == 2) {
        vector<int> x(h);
        int start = rnd.next(0, 100);
        int step = rnd.next(1, 20);
        for (int i = 0; i < h; ++i) {
            x[i] = start + i * i * step + rnd.next(0, step);
        }
        return x;
    }

    if (mode == 3) {
        vector<int> x(h);
        int end = rnd.next(999000, 1000000);
        int step = rnd.next(1, 20);
        for (int i = 0; i < h; ++i) {
            int j = h - 1 - i;
            x[i] = end - j * j * step - rnd.next(0, step);
        }
        sort(x.begin(), x.end());
        return x;
    }

    vector<int> pool;
    int center = rnd.next(100, 999900);
    int width = rnd.next(h, 300);
    int lo = max(0, center - width);
    int hi = min(1000000, center + width);
    for (int v = lo; v <= hi; ++v) {
        pool.push_back(v);
    }
    if ((int)pool.size() < h) {
        return makeByGaps(h, 1, 10);
    }
    return makePicked(h, pool);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 4);
        int h;
        if (mode == 1) {
            h = rnd.next(2, 14);
        } else if (rnd.next(0, 9) == 0) {
            h = rnd.next(31, 80);
        } else {
            h = rnd.next(2, 30);
        }

        vector<int> x = makeCase(h, mode);
        x.erase(unique(x.begin(), x.end()), x.end());
        while ((int)x.size() < h) {
            x = makeByGaps(h, 1, 20);
        }

        int c;
        if (rnd.next(0, 4) == 0) {
            c = 2;
        } else if (rnd.next(0, 4) == 0) {
            c = h;
        } else {
            c = rnd.next(2, h);
        }

        println(h, c);
        println(x);
    }

    return 0;
}
