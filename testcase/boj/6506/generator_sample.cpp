#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

static vector<int> makeValues(int n) {
    vector<int> values;
    int start = rnd.next(-9000, 9000 - n);
    int step = rnd.next(1, 7);
    for (int i = 0; i < n; ++i) {
        values.push_back(start + i * step);
    }
    return values;
}

static vector<int> zigzagOrder(int n) {
    vector<int> order;
    int lo = 0;
    int hi = n - 1;
    while (lo <= hi) {
        order.push_back(lo++);
        if (lo <= hi) {
            order.push_back(hi--);
        }
    }
    return order;
}

static vector<int> makeSequence(int n, int mode) {
    vector<int> values = makeValues(n);
    vector<int> seq;

    if (mode == 0) {
        seq = values;
    } else if (mode == 1) {
        seq = values;
        reverse(seq.begin(), seq.end());
    } else if (mode == 2) {
        seq = values;
        shuffle(seq.begin(), seq.end());
    } else if (mode == 3) {
        for (int idx : zigzagOrder(n)) {
            seq.push_back(values[idx]);
        }
    } else if (mode == 4) {
        int split = rnd.next(1, n);
        for (int i = split - 1; i >= 0; --i) {
            seq.push_back(values[i]);
        }
        for (int i = n - 1; i >= split; --i) {
            seq.push_back(values[i]);
        }
    } else {
        seq = values;
        int swaps = rnd.next(1, max(1, n / 2));
        for (int i = 0; i < swaps; ++i) {
            swap(seq[rnd.next(n)], seq[rnd.next(n)]);
        }
    }

    return seq;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int tests = rnd.next(3, 8);
    for (int tc = 0; tc < tests; ++tc) {
        int n;
        if (tc == 0 && rnd.next(2) == 0) {
            n = 1;
        } else {
            n = rnd.next(2, 25);
        }

        int mode = rnd.next(0, 5);
        int k;
        if (mode == 0 && rnd.next(3) == 0) {
            k = rnd.next(max(1, n - 3), n);
        } else if (mode == 1 && rnd.next(2) == 0) {
            k = rnd.next(1, min(n, 3));
        } else {
            k = rnd.next(1, n);
        }

        println(n, k);
        println(makeSequence(n, mode));
    }
    println(0, 0);

    return 0;
}
