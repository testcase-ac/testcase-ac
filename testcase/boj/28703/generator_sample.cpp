#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int boundedDouble(int base, int shifts) {
    long long value = base;
    while (shifts-- > 0 && value <= 500000000) value *= 2;
    return static_cast<int>(value);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    vector<int> a;

    if (mode == 0) {
        int n = rnd.next(1, 3);
        int value = rnd.next(1, 1000000000);
        a.assign(n, value);
    } else if (mode == 1) {
        int n = rnd.next(2, 8);
        int low = rnd.next(1, 20);
        int high = rnd.next(900000000, 1000000000);
        a.push_back(low);
        a.push_back(high);
        while (static_cast<int>(a.size()) < n) a.push_back(rnd.next(low, min(high, low + 200)));
    } else if (mode == 2) {
        int n = rnd.next(2, 10);
        int core = 2 * rnd.next(0, 30) + 1;
        for (int i = 0; i < n; ++i) a.push_back(boundedDouble(core, rnd.next(0, 20)));
    } else if (mode == 3) {
        int n = rnd.next(2, 12);
        int start = rnd.next(1, 200);
        for (int i = 0; i < n; ++i) a.push_back(start + rnd.next(0, 20));
    } else if (mode == 4) {
        int n = rnd.next(2, 9);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 1) == 0) {
                a.push_back(rnd.next(1, 1024));
            } else {
                a.push_back(rnd.next(999999000, 1000000000));
            }
        }
    } else if (mode == 5) {
        int n = rnd.next(3, 12);
        int base = rnd.next(1, 1000);
        for (int i = 0; i < n; ++i) a.push_back(boundedDouble(base + rnd.next(0, 5), rnd.next(0, 15)));
    } else {
        int n = rnd.next(2, 15);
        int upper = rnd.next(1, 1000000);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(1, upper));
    }

    shuffle(a.begin(), a.end());

    println(static_cast<int>(a.size()));
    println(a);

    return 0;
}
