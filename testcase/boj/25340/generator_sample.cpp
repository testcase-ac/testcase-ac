#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

struct Light {
    int a;
    int b;
    int c;
    int d;
};

long long arriveAt(long long start, const vector<Light>& lights, const vector<int>& e) {
    long long t = start + e[0];
    for (int i = 0; i < (int)lights.size(); ++i) {
        const Light& light = lights[i];
        if (t < light.c) {
            t = light.c;
        }

        long long cycle = (t - light.c) / light.a;
        if (t + light.d > light.c + light.a * cycle + light.b) {
            t = light.c + light.a * (cycle + 1);
        }
        t += light.d + e[i + 1];
    }
    return t;
}

Light randomLight(int mode) {
    if (mode == 0) {
        int a = rnd.next(2, 8);
        int b = rnd.next(1, a - 1);
        int d = rnd.next(1, b);
        int c = rnd.next(0, 8);
        return {a, b, c, d};
    }

    if (mode == 1) {
        int a = rnd.next(900, 1000);
        int b = rnd.next(a - 5, a - 1);
        int d = rnd.next(max(1, b - 5), b);
        int c = rnd.next(950, 1000);
        return {a, b, c, d};
    }

    int a = rnd.next(3, 30);
    int b = rnd.next(1, a - 1);
    int d = rnd.next(1, b);
    int c = rnd.next(0, 1000);
    return {a, b, c, d};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int tc = rnd.next(5, 12);
    println(tc);

    for (int test = 0; test < tc; ++test) {
        int mode = test % 5;
        int n = (mode == 1 ? rnd.next(1, 2) : rnd.next(1, 7));

        vector<Light> lights;
        vector<int> e(n + 1);
        for (int i = 0; i < n; ++i) {
            lights.push_back(randomLight(mode == 4 ? 1 : mode));
        }
        for (int i = 0; i <= n; ++i) {
            if (mode == 1) {
                e[i] = rnd.next(900, 1000);
            } else if (mode == 2) {
                e[i] = rnd.next(1, 3);
            } else {
                e[i] = rnd.next(1, 25);
            }
        }

        long long start = rnd.next(0, mode == 4 ? 1000000 : 80);
        long long exact = arriveAt(start, lights, e);
        long long t = exact;
        if (mode == 0) {
            t = max(1LL, exact + rnd.next(-2, 2));
        } else if (mode == 2) {
            t = max(1LL, arriveAt(0, lights, e) + rnd.next(0, 20));
        } else if (mode == 3) {
            t = rnd.next(1, 40);
        }
        t = min(t, 1000000000LL);

        println(n, t);
        for (const Light& light : lights) {
            println(light.a, light.b, light.c, light.d);
        }
        println(e);
    }

    return 0;
}
