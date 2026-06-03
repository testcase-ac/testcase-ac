#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, mode == 5 ? 35 : 18);
    vector<pair<int, int>> jobs;
    jobs.reserve(n);

    if (mode == 0) {
        int now = rnd.next(0, 30);
        for (int i = 0; i < n; ++i) {
            int t = rnd.next(1, 25);
            now += t + rnd.next(0, 12);
            jobs.push_back({t, now});
        }
    } else if (mode == 1) {
        int total = 0;
        for (int i = 0; i < n; ++i) {
            int t = rnd.next(1, 30);
            total += t;
            int s = rnd.next(1, max(1, total - rnd.next(1, 20)));
            jobs.push_back({t, s});
        }
    } else if (mode == 2) {
        int deadline = rnd.next(1, 250);
        for (int i = 0; i < n; ++i) {
            int t = rnd.next(1, 40);
            jobs.push_back({t, deadline});
        }
    } else if (mode == 3) {
        int now = rnd.next(0, 20);
        for (int i = 0; i < n; ++i) {
            int t = rnd.next(1, 20);
            now += t;
            int slack = rnd.next(0, 3) == 0 ? 0 : rnd.next(1, 8);
            jobs.push_back({t, now + slack});
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            int t = rnd.next(1, 1000);
            int s = rnd.next(1, 1000000);
            jobs.push_back({t, s});
        }
    } else {
        int base = rnd.next(900000, 1000000);
        for (int i = 0; i < n; ++i) {
            int t = rnd.next(1, 1000);
            int s = max(1, base - rnd.next(0, 50000));
            jobs.push_back({t, s});
        }
    }

    shuffle(jobs.begin(), jobs.end());

    println(n);
    for (auto [t, s] : jobs) {
        println(t, s);
    }

    return 0;
}
