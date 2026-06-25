#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> values;
    auto add = [&](int n) {
        if (1 <= n && n <= 10000000) {
            values.push_back(n);
        }
    };

    int mode = rnd.next(0, 4);

    if (mode == 0) {
        int upper = rnd.next(1, 20);
        for (int n = 1; n <= upper; ++n) {
            add(n);
        }
    } else if (mode == 1) {
        int base = 1 << rnd.next(0, 23);
        for (int delta = -3; delta <= 3; ++delta) {
            add(base + delta);
        }
        while ((int)values.size() < 20) {
            int other = 1 << rnd.next(0, 23);
            add(other + rnd.next(-5, 5));
        }
    } else if (mode == 2) {
        int center = rnd.next(1, 10000000);
        int radius = rnd.next(0, 50);
        for (int delta = -radius; delta <= radius && (int)values.size() < 20; ++delta) {
            add(center + delta);
        }
    } else if (mode == 3) {
        add(1);
        add(2);
        add(9999999);
        add(10000000);
        while ((int)values.size() < 20) {
            add(rnd.next(9000000, 10000000));
        }
    } else {
        int count = rnd.next(1, 20);
        for (int i = 0; i < count; ++i) {
            if (rnd.next(0, 2) == 0) {
                add(rnd.next(1, 200));
            } else {
                add(rnd.next(1, 10000000));
            }
        }
    }

    shuffle(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());
    while (values.empty()) {
        add(rnd.next(1, 10000000));
    }
    if ((int)values.size() > 20) {
        values.resize(20);
    }

    println((int)values.size());
    for (int n : values) {
        println(n);
    }

    return 0;
}
