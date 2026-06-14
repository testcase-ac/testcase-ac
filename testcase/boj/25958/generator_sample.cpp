#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

bool isPrime(int x) {
    if (x < 2) {
        return false;
    }
    for (int d = 2; 1LL * d * d <= x; ++d) {
        if (x % d == 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int m;
    if (mode == 0) {
        m = rnd.next(1, 20);
    } else if (mode == 1) {
        m = rnd.next(21, 200);
    } else if (mode == 2) {
        m = rnd.next(201, 1000);
    } else if (mode == 3) {
        m = rnd.next(1001, 5000);
    } else if (mode == 4) {
        m = rnd.any(vector<int>{1, 2, 9, 10, 99, 100, 999, 1000, 4999, 5000});
    } else {
        int base = rnd.any(vector<int>{90, 99, 100, 999, 1000, 4990, 5000});
        m = max(1, min(5000, base + rnd.next(-8, 8)));
    }

    int k;
    do {
        k = rnd.next(1000000, 10000000);
    } while (!isPrime(k));

    println(m, k);

    return 0;
}
