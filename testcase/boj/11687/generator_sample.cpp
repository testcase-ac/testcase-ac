#include "testlib.h"

#include <vector>
using namespace std;

long long trailingZeroes(long long n) {
    long long result = 0;
    while (n > 0) {
        n /= 5;
        result += n;
    }
    return result;
}

int randomAttainableM() {
    while (true) {
        long long n = 5LL * rnd.next(1, 40000000);
        long long m = trailingZeroes(n);
        if (1 <= m && m <= 100000000) {
            return static_cast<int>(m);
        }
    }
}

int randomSkippedM() {
    for (int attempt = 0; attempt < 100; ++attempt) {
        long long n = 25LL * rnd.next(1, 16000000);
        long long before = trailingZeroes(n - 1);
        long long after = trailingZeroes(n);
        if (after - before > 1) {
            long long m = rnd.next(before + 1, after - 1);
            if (1 <= m && m <= 100000000) {
                return static_cast<int>(m);
            }
        }
    }
    return 5;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> anchors = {
        1,
        2,
        3,
        4,
        5,
        6,
        24,
        25,
        26,
        124,
        125,
        126,
        99999998,
        99999999,
        100000000
    };

    int mode = rnd.next(6);
    int m;

    if (mode == 0) {
        m = rnd.next(1, 30);
    } else if (mode == 1) {
        m = rnd.any(anchors);
    } else if (mode == 2) {
        m = randomAttainableM();
    } else if (mode == 3) {
        m = randomSkippedM();
    } else if (mode == 4) {
        int center = rnd.any(vector<int>{25, 125, 625, 3125, 15625, 78125});
        int lo = max(1, center - 5);
        int hi = min(100000000, center + 5);
        m = rnd.next(lo, hi);
    } else {
        m = rnd.next(1, 100000000);
    }

    println(m);
    return 0;
}
