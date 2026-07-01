#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

struct Light {
    long long x;
    long long a;
    long long g;
    long long r;
};

long long clampTiming(long long value) {
    return max(1LL, min(1000000000LL, value));
}

Light makeLight(long long x, int style) {
    long long a = 1;
    long long g = 1;
    long long r = 1;

    if (style == 0) {
        a = rnd.next(1LL, x);
        g = rnd.next((long long)max(1LL, x - a), (long long)max(1LL, x - a + 5));
        r = rnd.next(1LL, 12LL);
    } else if (style == 1) {
        a = rnd.next(1LL, min(x + 8, 1000000000LL));
        g = rnd.next(1LL, 8LL);
        r = rnd.next(1LL, 8LL);
    } else if (style == 2) {
        a = rnd.next(1LL, x);
        g = max(1LL, x - a);
        r = rnd.next(1LL, 20LL);
    } else if (style == 3) {
        long long cycle = rnd.next(3LL, 20LL);
        g = rnd.next(1LL, cycle - 2);
        r = cycle - g;
        long long mod = rnd.next(g + 1, cycle - 1);
        a = x - mod;
        while (a < 1) a += cycle;
    } else {
        a = rnd.next(max(1LL, x - 3), min(1000000000LL, x + 3));
        g = rnd.next(1LL, 1000000000LL);
        r = rnd.next(1LL, 1000000000LL);
    }

    return {x, clampTiming(a), clampTiming(g), clampTiming(r)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = mode == 0 ? 1 : rnd.next(2, mode == 4 ? 12 : 7);
    long long d = mode == 4 ? rnd.next(900000000LL, 1000000000LL)
                            : rnd.next((long long)n + 2, 80LL);

    set<long long> used;
    vector<Light> lights;
    for (int i = 0; i < n; ++i) {
        long long x;
        if (mode == 4 && i == 0) {
            x = d - 1;
        } else {
            do {
                x = rnd.next(1LL, d - 1);
            } while (used.count(x));
        }
        used.insert(x);

        int style = mode;
        if (mode == 1 || mode == 2) style = rnd.next(4);
        lights.push_back(makeLight(x, style));
    }

    if (mode == 3 && !lights.empty()) {
        lights[0] = makeLight(lights[0].x, 3);
    }

    shuffle(lights.begin(), lights.end());

    println(n, d);
    for (const Light& light : lights) {
        println(light.x, light.a, light.g, light.r);
    }

    return 0;
}
