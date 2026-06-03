#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

static vector<int> randomSet(int m, int n) {
    vector<int> values(m);
    iota(values.begin(), values.end(), 1);
    shuffle(values.begin(), values.end());
    values.resize(n);
    sort(values.begin(), values.end());
    return values;
}

static vector<int> clusteredSet(int m, int n) {
    int width = rnd.next(n, min(m, n + rnd.next(0, 12)));
    int start = rnd.next(1, m - width + 1);
    vector<int> values(width);
    iota(values.begin(), values.end(), start);
    shuffle(values.begin(), values.end());
    values.resize(n);
    sort(values.begin(), values.end());
    return values;
}

static vector<int> periodicSet(int m, int repeats, int blockSize) {
    int period = m / repeats;
    vector<int> offsets;
    while ((int)offsets.size() < blockSize) {
        int x = rnd.next(0, period - 1);
        if (find(offsets.begin(), offsets.end(), x) == offsets.end()) offsets.push_back(x);
    }
    sort(offsets.begin(), offsets.end());

    vector<int> values;
    for (int r = 0; r < repeats; ++r) {
        for (int offset : offsets) values.push_back(r * period + offset + 1);
    }
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(6, 12);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 4);
        int m;
        vector<int> values;

        if (mode == 0) {
            m = rnd.next(1, 1000000);
            values = {rnd.next(1, m)};
        } else if (mode == 1) {
            m = rnd.next(1, 40);
            values.resize(m);
            iota(values.begin(), values.end(), 1);
        } else if (mode == 2) {
            m = rnd.next(2, 80);
            int n = rnd.next(2, min(m, 18));
            values = randomSet(m, n);
        } else if (mode == 3) {
            m = rnd.next(2, 120);
            int n = rnd.next(2, min(m, 20));
            values = clusteredSet(m, n);
        } else {
            int repeats = rnd.any(vector<int>{2, 3, 4, 5, 6, 8});
            int period = rnd.next(2, 18);
            m = repeats * period;
            int blockSize = rnd.next(1, min(period, 5));
            values = periodicSet(m, repeats, blockSize);
        }

        println(m, (int)values.size());
        for (int x : values) println(x);
    }

    return 0;
}
