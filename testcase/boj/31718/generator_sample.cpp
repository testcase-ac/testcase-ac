#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MAX_A = 1000000000;

int valueFromCore(int core, int maxShift = 30) {
    long long value = core;
    int limit = 0;
    while (limit < maxShift && value * 2 <= MAX_A) {
        value *= 2;
        ++limit;
    }

    int shift = rnd.next(0, limit);
    value = core;
    while (shift--) value *= 2;
    return static_cast<int>(value);
}

int randomOddCore(int hi) {
    int core = rnd.next(1, hi);
    if (core % 2 == 0) --core;
    return max(core, 1);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 12);
        int core = randomOddCore(50);
        for (int i = 0; i < n; ++i) a.push_back(valueFromCore(core));
    } else if (mode == 1) {
        n = rnd.next(6, 25);
        int groups = rnd.next(2, 5);
        vector<int> cores;
        for (int i = 0; i < groups; ++i) cores.push_back(randomOddCore(80));
        for (int i = 0; i < n; ++i) a.push_back(valueFromCore(rnd.any(cores)));
    } else if (mode == 2) {
        n = rnd.next(8, 35);
        int core = randomOddCore(1000000);
        int repeated = valueFromCore(core);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 2) == 0) {
                a.push_back(repeated);
            } else {
                a.push_back(valueFromCore(randomOddCore(200)));
            }
        }
    } else if (mode == 3) {
        n = rnd.next(5, 20);
        vector<int> boundary = {1, 2, 4, 536870912, 999999937, 999999999, MAX_A};
        for (int i = 0; i < n; ++i) a.push_back(rnd.any(boundary));
    } else if (mode == 4) {
        n = rnd.next(30, 120);
        for (int i = 0; i < n; ++i) {
            int core = (rnd.next(0, 3) == 0) ? randomOddCore(1000) : randomOddCore(MAX_A);
            a.push_back(valueFromCore(core));
        }
    } else {
        n = rnd.next(1000, 200000);
        int groups = rnd.next(1, 20);
        vector<int> cores;
        for (int i = 0; i < groups; ++i) cores.push_back(randomOddCore(100000));
        for (int i = 0; i < n; ++i) a.push_back(valueFromCore(rnd.any(cores)));
    }

    shuffle(a.begin(), a.end());

    println(n);
    println(a);

    return 0;
}
