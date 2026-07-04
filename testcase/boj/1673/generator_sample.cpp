#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long N_MIN = 2;
    const long long N_MAX = 1000000000LL;

    int tc = rnd.next(3, 10);
    vector<pair<long long, long long>> cases;

    for (int i = 0; i < tc; ++i) {
        int mode = rnd.next(0, 7);
        long long n = N_MIN;
        long long k = N_MIN;

        if (mode == 0) {
            n = rnd.next(N_MIN, 80LL);
            k = n;
        } else if (mode == 1) {
            k = rnd.next(N_MIN, 80LL);
            n = min(N_MAX, k + rnd.next(1LL, 3LL));
        } else if (mode == 2) {
            k = rnd.next(N_MIN, 30LL);
            long long multiplier = rnd.next(2LL, 25LL);
            n = k * multiplier;
        } else if (mode == 3) {
            k = rnd.next(N_MIN, 30LL);
            long long multiplier = rnd.next(2LL, 25LL);
            n = k * multiplier - 1;
        } else if (mode == 4) {
            k = rnd.next(2LL, 10LL);
            n = rnd.next(200LL, 5000LL);
        } else if (mode == 5) {
            n = rnd.next(N_MAX - 10000, N_MAX);
            k = rnd.next(2LL, n);
        } else if (mode == 6) {
            k = rnd.next(N_MAX - 10000, N_MAX);
            n = rnd.next(k, N_MAX);
        } else {
            n = rnd.next(N_MIN, 1000LL);
            k = rnd.next(N_MIN, n);
        }

        cases.push_back({n, k});
    }

    shuffle(cases.begin(), cases.end());
    for (const auto& testCase : cases) {
        println(testCase.first, testCase.second);
    }

    return 0;
}
