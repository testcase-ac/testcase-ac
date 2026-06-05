#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> luckyNumbers() {
    vector<int> values;
    for (int len = 1; len <= 6; ++len) {
        int masks = 1 << len;
        for (int mask = 0; mask < masks; ++mask) {
            int value = 0;
            for (int bit = len - 1; bit >= 0; --bit) {
                value = value * 10 + ((mask & (1 << bit)) ? 7 : 4);
            }
            values.push_back(value);
        }
    }
    sort(values.begin(), values.end());
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int limit = 1000000;
    vector<int> lucky = luckyNumbers();

    int mode = rnd.next(0, 7);
    int n = 1;

    if (mode == 0) {
        vector<int> edges = {1, 2, 3, 4, 7, 8, 11, 12, 13, 44, 47, 74, 77, limit - 1, limit};
        n = rnd.any(edges);
    } else if (mode == 1) {
        n = rnd.any(lucky);
    } else if (mode == 2) {
        int terms = rnd.next(2, 10);
        n = 0;
        for (int i = 0; i < terms; ++i) {
            vector<int> choices;
            for (int value : lucky) {
                if (n + value <= limit) choices.push_back(value);
            }
            if (choices.empty()) break;
            n += rnd.any(choices);
        }
    } else if (mode == 3) {
        int terms = rnd.next(20, 250);
        n = 0;
        for (int i = 0; i < terms && n + 4 <= limit; ++i) {
            n += rnd.next(0, 1) ? 4 : 7;
        }
    } else if (mode == 4) {
        int base = rnd.any(lucky);
        int delta = rnd.next(-10, 10);
        n = min(limit, max(1, base + delta));
    } else if (mode == 5) {
        n = limit - rnd.next(0, 2000);
    } else {
        n = rnd.next(1, limit);
    }

    println(n);
    return 0;
}
