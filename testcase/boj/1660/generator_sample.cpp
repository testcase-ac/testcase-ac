#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int tetra(int n) {
    return n * (n + 1) * (n + 2) / 6;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int limit = 300000;

    vector<int> values;
    for (int i = 1; tetra(i) <= limit; ++i) {
        values.push_back(tetra(i));
    }

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 40);
    } else if (mode == 1) {
        n = rnd.any(values);
    } else if (mode == 2) {
        int base = rnd.any(values);
        int delta = rnd.next(-8, 8);
        n = min(limit, max(1, base + delta));
    } else if (mode == 3) {
        int parts = rnd.next(2, 5);
        n = 0;
        for (int i = 0; i < parts; ++i) {
            int remaining = limit - n;
            vector<int> candidates;
            for (int value : values) {
                if (value <= remaining) candidates.push_back(value);
            }
            n += rnd.any(candidates);
        }
    } else if (mode == 4) {
        n = rnd.next(250000, limit);
    } else {
        int base = values.back();
        n = rnd.next(max(1, base - 5000), limit);
    }

    println(n);
    return 0;
}
