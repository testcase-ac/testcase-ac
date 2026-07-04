#include "testlib.h"

#include <utility>
#include <vector>
using namespace std;

using Glass = pair<int, int>;

int boundedAround(int center, int radius) {
    int lo = max(1, center - radius);
    int hi = min(200000, center + radius);
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int t = 1;
    vector<Glass> glasses;

    if (mode == 0) {
        t = rnd.next(1, 20);
        int n = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            glasses.push_back({rnd.next(1, t), 1});
        }
    } else if (mode == 1) {
        t = rnd.next(20, 200);
        int n = rnd.next(8, 40);
        int period = rnd.next(2, 12);
        for (int i = 0; i < n; ++i) {
            glasses.push_back({rnd.next(1, min(t, 50)), period});
        }
    } else if (mode == 2) {
        t = rnd.next(30, 300);
        int n = rnd.next(10, 50);
        vector<int> periods = {2, 3, 4, 5, 6, 10, 12};
        for (int i = 0; i < n; ++i) {
            int a = (i % 3 == 0) ? rnd.next(1, min(t, 20)) : rnd.next(1, 200000);
            glasses.push_back({a, rnd.any(periods)});
        }
    } else if (mode == 3) {
        t = rnd.next(50, 500);
        int n = rnd.next(10, 60);
        int start = rnd.next(1, 200000 - n);
        for (int i = 0; i < n; ++i) {
            int a = rnd.next(1, min(200000, t + 40));
            glasses.push_back({a, start + i});
        }
    } else if (mode == 4) {
        t = rnd.any(vector<int>{1, 2, 199999, 200000});
        int n = rnd.next(2, 12);
        glasses.push_back({1, 200000});
        glasses.push_back({200000, 1});
        for (int i = 2; i < n; ++i) {
            int edge = rnd.any(vector<int>{1, 2, 199999, 200000});
            glasses.push_back({edge, boundedAround(edge, 3)});
        }
    } else if (mode == 5) {
        t = rnd.next(5, 80);
        int n = rnd.next(5, 30);
        for (int i = 0; i < n; ++i) {
            int a = rnd.next(t + 1, 200000);
            int b = rnd.next(1, 200000);
            glasses.push_back({a, b});
        }
    } else {
        t = rnd.next(1, 1000);
        int n = rnd.next(1, 80);
        int maxA = rnd.next(1, 200000);
        int maxB = rnd.next(1, 200000);
        for (int i = 0; i < n; ++i) {
            glasses.push_back({rnd.next(1, maxA), rnd.next(1, maxB)});
        }
    }

    shuffle(glasses.begin(), glasses.end());

    println((int)glasses.size(), t);
    for (const Glass& glass : glasses) {
        println(glass.first, glass.second);
    }

    return 0;
}
