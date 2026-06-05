#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;
    vector<pair<int, int>> charms;

    if (mode == 0) {
        n = rnd.next(1, 4);
        m = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            charms.push_back({rnd.next(1, 8), rnd.next(1, 20)});
        }
    } else if (mode == 1) {
        n = rnd.next(3, 12);
        m = rnd.next(1, 30);
        int heavyStart = min(400, m + 1);
        for (int i = 0; i < n; ++i) {
            if (heavyStart <= 400 && rnd.next(0, 2) != 0) {
                charms.push_back({rnd.next(heavyStart, 400), rnd.next(1, 100)});
            } else {
                charms.push_back({rnd.next(1, min(400, max(1, m))), rnd.next(1, 100)});
            }
        }
    } else if (mode == 2) {
        n = rnd.next(5, 20);
        int w = rnd.next(1, 30);
        m = rnd.next(w, min(12880, w * rnd.next(1, n)));
        for (int i = 0; i < n; ++i) {
            charms.push_back({w, rnd.next(1, 100)});
        }
    } else if (mode == 3) {
        n = rnd.next(4, 14);
        m = rnd.next(10, 80);
        int remaining = m;
        for (int i = 0; i < n; ++i) {
            int maxWeight = min(400, max(1, remaining));
            int w = rnd.next(1, maxWeight);
            if (rnd.next(0, 3) == 0) {
                w = rnd.next(1, min(400, m));
            }
            charms.push_back({w, rnd.next(1, 100)});
            remaining = max(1, remaining - w);
        }
    } else if (mode == 4) {
        n = rnd.next(12, 35);
        m = rnd.next(1000, 12880);
        for (int i = 0; i < n; ++i) {
            int w = rnd.next(1, 400);
            int d = rnd.next(1, 100);
            if (rnd.next(0, 4) == 0) {
                w = rnd.next(350, 400);
            }
            charms.push_back({w, d});
        }
    } else {
        n = rnd.next(8, 28);
        m = rnd.next(20, 250);
        int lowWeight = rnd.next(1, 10);
        int highWeight = rnd.next(lowWeight, min(400, lowWeight + rnd.next(5, 60)));
        int lowValue = rnd.next(1, 50);
        int highValue = rnd.next(lowValue, min(100, lowValue + rnd.next(5, 50)));
        for (int i = 0; i < n; ++i) {
            charms.push_back({rnd.next(lowWeight, highWeight), rnd.next(lowValue, highValue)});
        }
    }

    shuffle(charms.begin(), charms.end());

    println(n, m);
    for (auto charm : charms) {
        println(charm.first, charm.second);
    }

    return 0;
}
