#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 18);
    int b = rnd.next(2, 18);
    int mode = rnd.next(0, 4);

    vector<long long> snow(n, 0);
    long long maxSnow = rnd.next(0, 30);
    for (int i = 1; i + 1 < n; ++i) {
        if (mode == 0) {
            snow[i] = rnd.next(0LL, maxSnow);
        } else if (mode == 1) {
            snow[i] = (i % 2 == 0 ? rnd.next(0LL, maxSnow / 2 + 1) : rnd.next(maxSnow / 2, maxSnow));
        } else if (mode == 2) {
            snow[i] = (rnd.next(0, 4) == 0 ? maxSnow : rnd.next(0LL, maxSnow));
        } else if (mode == 3) {
            snow[i] = rnd.next(0LL, min<long long>(maxSnow, i + 3));
        } else {
            snow[i] = rnd.next(0LL, min<long long>(maxSnow, n - i + 2));
        }
    }

    long long deepest = *max_element(snow.begin(), snow.end());
    vector<pair<long long, int>> boots;
    boots.reserve(b);

    int strongAt = rnd.next(0, b - 1);
    for (int i = 0; i < b; ++i) {
        long long depth;
        int step;
        if (i == strongAt) {
            depth = deepest;
            step = rnd.next(max(1, n / 2), n - 1);
        } else if (mode == 0) {
            depth = rnd.next(0LL, maxSnow);
            step = rnd.next(1, n - 1);
        } else if (mode == 1) {
            depth = rnd.next(0LL, maxSnow);
            step = rnd.next(1, min(n - 1, 3));
        } else if (mode == 2) {
            depth = (rnd.next(0, 2) == 0 ? deepest : rnd.next(0LL, maxSnow));
            step = rnd.next(1, n - 1);
        } else if (mode == 3) {
            depth = rnd.next(0LL, maxSnow);
            step = rnd.next(max(1, n / 3), n - 1);
        } else {
            depth = rnd.next(0LL, maxSnow);
            step = rnd.next(1, max(1, n / 3));
        }
        boots.emplace_back(depth, step);
    }

    boots.back().first = deepest;
    boots.back().second = n - 1;

    println(n, b);
    println(snow);
    for (const auto& boot : boots) {
        println(boot.first, boot.second);
    }

    return 0;
}
