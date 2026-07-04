#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

long long smallValue() {
    return rnd.next(1, 30);
}

long long mediumValue() {
    return rnd.next(31, 1000000);
}

long long largeValue() {
    return rnd.next(900000000, 1000000000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 20);
    vector<vector<long long>> cases;
    cases.reserve(T);

    for (int i = 0; i < T; ++i) {
        int mode = rnd.next(0, 5);
        long long n, x, t;

        if (mode == 0) {
            n = smallValue();
            x = smallValue();
            t = smallValue();
        } else if (mode == 1) {
            n = rnd.next(1, 5);
            x = mediumValue();
            t = smallValue();
        } else if (mode == 2) {
            n = mediumValue();
            x = smallValue();
            t = mediumValue();
        } else if (mode == 3) {
            n = largeValue();
            x = rnd.next(1, 1000);
            t = largeValue();
        } else if (mode == 4) {
            long long base = rnd.next(1, 1000000);
            n = base;
            x = max(1LL, base + rnd.next(-10, 10));
            t = max(1LL, base + rnd.next(-10, 10));
        } else {
            n = rnd.any(vector<long long>{1LL, 2LL, 3LL, 1000000000LL});
            x = rnd.any(vector<long long>{1LL, 2LL, 1000000000LL});
            t = rnd.any(vector<long long>{1LL, 2LL, 1000000000LL});
        }

        cases.push_back({n, x, t});
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (const auto& tc : cases) {
        println(tc[0], tc[1], tc[2]);
    }

    return 0;
}
