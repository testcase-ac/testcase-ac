#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Light {
    long long x;
    long long t;
    long long s;
};

long long randomTime(int mode) {
    if (mode == 0) {
        return 1;
    }
    if (mode == 1) {
        return rnd.next(1, 6);
    }
    if (mode == 2) {
        return rnd.next(999999900LL, 1000000000LL);
    }
    return rnd.next(1LL, 1000000000LL);
}

long long randomOffset(long long t, int mode) {
    if (mode == 0 || t == 1) {
        return 0;
    }
    if (mode == 1) {
        return t - 1;
    }
    if (mode == 2) {
        return rnd.next(0LL, min(5LL, t - 1));
    }
    return rnd.next(0LL, t - 1);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    long long n;
    int k;
    if (mode == 0) {
        n = rnd.next(1LL, 20LL);
        k = 0;
    } else if (mode == 1) {
        n = rnd.next(2LL, 8LL);
        k = rnd.next(1, (int)n - 1);
    } else if (mode == 2) {
        n = rnd.next(8LL, 30LL);
        k = rnd.next(max(1, (int)n - 8), (int)n - 1);
    } else if (mode == 3) {
        n = rnd.next(2LL, 1000000000LL);
        k = 1;
    } else if (mode == 4) {
        n = rnd.next(20LL, 200LL);
        k = rnd.next(2, 20);
    } else if (mode == 5) {
        n = rnd.next(100000000LL, 1000000000LL);
        k = rnd.next(2, 35);
    } else {
        n = rnd.next(3LL, 60LL);
        k = rnd.next(1, min(25, (int)n - 1));
    }

    vector<long long> positions;
    if (n - 1 <= 200) {
        for (long long x = 1; x <= n - 1; ++x) {
            positions.push_back(x);
        }
        shuffle(positions.begin(), positions.end());
        positions.resize(k);
    } else {
        while ((int)positions.size() < k) {
            long long x;
            if (rnd.next(0, 5) == 0) {
                x = rnd.any(vector<long long>{1LL, 2LL, n - 2, n - 1});
            } else {
                x = rnd.next(1LL, n - 1);
            }
            if (find(positions.begin(), positions.end(), x) == positions.end()) {
                positions.push_back(x);
            }
        }
    }

    vector<Light> lights;
    for (int i = 0; i < k; ++i) {
        int timeMode = rnd.next(0, 3);
        if (mode == 1) {
            timeMode = rnd.next(0, 1);
        } else if (mode == 5) {
            timeMode = rnd.next(1, 3);
        }

        long long t = randomTime(timeMode);
        long long s = randomOffset(t, rnd.next(0, 3));
        lights.push_back({positions[i], t, s});
    }

    if (mode == 6) {
        sort(lights.begin(), lights.end(), [](const Light& a, const Light& b) {
            return a.x < b.x;
        });
    } else {
        shuffle(lights.begin(), lights.end());
    }

    println(n, k);
    for (const Light& light : lights) {
        println(light.x, light.t, light.s);
    }

    return 0;
}
