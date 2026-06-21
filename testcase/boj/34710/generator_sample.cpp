#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, mode == 5 ? 40 : 18);
    vector<pair<int, int>> tasks;
    tasks.reserve(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            int t = rnd.next(1, 25);
            int l = rnd.next(0, t);
            tasks.emplace_back(t, l);
        }
    } else if (mode == 1) {
        int t = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            int l = rnd.next(0, min(200000, t + rnd.next(0, 4)));
            tasks.emplace_back(t, l);
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            int t = rnd.next(1, 20);
            int l = rnd.next(t + 1, min(200000, t + 12));
            tasks.emplace_back(t, l);
        }
    } else if (mode == 3) {
        int t = rnd.next(1, 8);
        int l = rnd.next(0, t);
        for (int i = 0; i < n; ++i) {
            t += rnd.next(0, 5);
            l += rnd.next(0, 4);
            l = min(l, 200000);
            tasks.emplace_back(min(t, 200000), l);
        }
    } else if (mode == 4) {
        int baseT = rnd.next(199980, 200000);
        for (int i = 0; i < n; ++i) {
            int t = rnd.next(max(1, baseT - 20), 200000);
            int l = rnd.next(max(0, t - 30), 200000);
            tasks.emplace_back(t, l);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            int t = rnd.next(1, 60);
            int l;
            if (rnd.next(0, 4) == 0) {
                l = rnd.next(t + 1, min(200000, t + 20));
            } else {
                l = rnd.next(0, t);
            }
            tasks.emplace_back(t, l);
        }
    }

    shuffle(tasks.begin(), tasks.end());

    println(n);
    for (auto [t, l] : tasks) {
        println(t, l);
    }

    return 0;
}
