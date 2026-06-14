#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

struct Ingredient {
    long long l;
    long long r;
    long long v;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 16);
    vector<Ingredient> a;

    if (mode == 0) {
        int center = rnd.next(-20, 20);
        for (int i = 0; i < n; ++i) {
            long long d = n - i + rnd.next(0, 2);
            a.push_back({center - d, center + d, rnd.next(1, 50)});
        }
    } else if (mode == 1) {
        long long l = rnd.next(-30, 20);
        long long r = rnd.next((int)l, 30);
        for (int i = 0; i < n; ++i) {
            int side = rnd.next(0, 2);
            if (side == 0) {
                long long rr = rnd.next((int)l, (int)r);
                a.push_back({l, rr, rnd.next(1, 100)});
            } else if (side == 1) {
                long long ll = rnd.next((int)l, (int)r);
                a.push_back({ll, r, rnd.next(1, 100)});
            } else {
                a.push_back({l, r, rnd.next(1, 100)});
            }
        }
    } else if (mode == 2) {
        long long cur = rnd.next(-80, -20);
        for (int i = 0; i < n; ++i) {
            long long len = rnd.next(0, 5);
            a.push_back({cur, cur + len, rnd.next(1, 80)});
            cur += len + rnd.next(1, 8);
        }
    } else if (mode == 3) {
        n = rnd.next(2, 10);
        a.push_back({-1000000000LL, 1000000000LL, rnd.next(1, 1000000000)});
        for (int i = 1; i < n; ++i) {
            long long l = rnd.next(-100, 100);
            long long r = rnd.next((int)l, 100);
            long long v = rnd.next(1, 1000000000);
            a.push_back({l, r, v});
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            long long x = rnd.next(-50, 50);
            a.push_back({x, x, rnd.next(1, 100)});
        }
    } else {
        for (int i = 0; i < n; ++i) {
            long long l = rnd.next(-40, 40);
            long long r = rnd.next((int)l, 40);
            a.push_back({l, r, rnd.next(1, 100)});
        }
    }

    shuffle(a.begin(), a.end());

    println((int)a.size());
    for (const auto& x : a) {
        println(x.l, x.r, x.v);
    }

    return 0;
}
