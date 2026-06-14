#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

namespace {

string makeBookNumber(int value, int decimals) {
    int scale = 1;
    for (int i = 0; i < decimals; ++i) {
        scale *= 10;
    }

    int whole = value / scale;
    int frac = value % scale;
    if (decimals == 0) {
        return to_string(whole);
    }

    string tail = to_string(frac);
    while ((int)tail.size() < decimals) {
        tail = "0" + tail;
    }
    return to_string(whole) + "." + tail;
}

vector<int> makeValues(int n, int decimals, int mode) {
    int scale = 1;
    for (int i = 0; i < decimals; ++i) {
        scale *= 10;
    }

    vector<int> values(n);
    if (mode == 0) {
        int base = rnd.next(1, 20 * scale);
        int step = rnd.next(1, max(1, 7 * scale));
        for (int i = 0; i < n; ++i) {
            values[i] = min(999 * scale - 1, base + i * step);
        }
    } else if (mode == 1) {
        int base = rnd.next(max(1, n), 999 * scale - 1);
        int step = rnd.next(1, max(1, 5 * scale));
        for (int i = 0; i < n; ++i) {
            values[i] = max(1, base - i * step);
        }
    } else if (mode == 2) {
        int lo = rnd.next(1, 20 * scale);
        int hi = min(999 * scale - 1, lo + rnd.next(1, 12 * scale));
        for (int i = 0; i < n; ++i) {
            values[i] = rnd.next(lo, hi);
        }
    } else if (mode == 3) {
        int center = rnd.next(1, 999 * scale - 1);
        for (int i = 0; i < n; ++i) {
            int delta = rnd.next(-3 * scale, 3 * scale);
            values[i] = min(999 * scale - 1, max(1, center + delta));
        }
    } else {
        vector<int> pool;
        int poolSize = rnd.next(2, min(10, max(2, n)));
        for (int i = 0; i < poolSize; ++i) {
            pool.push_back(rnd.next(1, 999 * scale - 1));
        }
        sort(pool.begin(), pool.end());
        for (int i = 0; i < n; ++i) {
            values[i] = rnd.any(pool);
        }
    }

    if (rnd.next(2) == 0) {
        shuffle(values.begin(), values.end());
    }
    if (mode == 0) {
        sort(values.begin(), values.end());
    }
    if (mode == 1) {
        sort(values.rbegin(), values.rend());
    }
    return values;
}

vector<int> makeWeights(int n, int mode) {
    vector<int> weights(n);
    if (mode == 0) {
        for (int& weight : weights) {
            weight = rnd.next(1, 20);
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            weights[i] = i % 2 == 0 ? rnd.next(8000, 10000) : rnd.next(1, 10);
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            weights[i] = rnd.next(1, 10000);
        }
    } else {
        int heavy = rnd.next(1000, 10000);
        int light = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            weights[i] = rnd.next(4) == 0 ? heavy : light;
        }
    }
    return weights;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    if (rnd.next(10) == 0) {
        n = rnd.next(80, 160);
    } else {
        n = rnd.next(1, 30);
    }

    int decimals = rnd.next(0, 3);
    int valueMode = rnd.next(0, 4);
    int weightMode = rnd.next(0, 3);

    vector<int> values = makeValues(n, decimals, valueMode);
    vector<string> books;
    for (int value : values) {
        books.push_back(makeBookNumber(value, decimals));
    }
    vector<int> weights = makeWeights(n, weightMode);

    println(n);
    println(books);
    println(weights);
    return 0;
}
