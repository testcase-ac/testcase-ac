#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 3);
    } else if (mode == 1) {
        n = rnd.next(4, 7);
    } else {
        n = rnd.next(2, 8);
    }
    int b = rnd.next(1, min(20, max(1, 3 * n)));

    vector<vector<int>> skill(n, vector<int>(n));
    if (mode == 0) {
        int lo = rnd.next(1, 12);
        int hi = rnd.next(lo, min(1000, lo + 30));
        for (int cow = 0; cow < n; ++cow) {
            for (int event = 0; event < n; ++event) {
                skill[cow][event] = rnd.next(lo, hi);
            }
        }
    } else if (mode == 1) {
        for (int cow = 0; cow < n; ++cow) {
            for (int event = 0; event < n; ++event) {
                int base = 5 + 4 * event + rnd.next(0, 9);
                int favorite = (cow == event ? rnd.next(20, 80) : 0);
                skill[cow][event] = min(1000, base + favorite);
            }
        }
    } else if (mode == 2) {
        for (int cow = 0; cow < n; ++cow) {
            for (int event = 0; event < n; ++event) {
                skill[cow][event] = rnd.next(850, 1000);
            }
        }
    } else {
        for (int cow = 0; cow < n; ++cow) {
            for (int event = 0; event < n; ++event) {
                int low = rnd.next(1, 35);
                int high = rnd.next(200, 1000);
                skill[cow][event] = (rnd.next(0, 3) == 0 ? high : low);
            }
        }
    }

    vector<int> eventBest(n);
    for (int event = 0; event < n; ++event) {
        for (int cow = 0; cow < n; ++cow) {
            eventBest[event] = max(eventBest[event], skill[cow][event]);
        }
    }
    vector<int> prefixBest(n);
    partial_sum(eventBest.begin(), eventBest.end(), prefixBest.begin());

    vector<pair<int, pair<int, int>>> bonuses;
    for (int i = 0; i < b; ++i) {
        int k = rnd.next(1, n);
        int around = prefixBest[k - 1];
        int p;
        if (i % 4 == 0) {
            p = rnd.next(1, min(40000, max(1, around)));
        } else if (i % 4 == 1) {
            p = min(40000, around + rnd.next(0, 1200));
        } else if (i % 4 == 2) {
            p = rnd.next(1, 40000);
        } else {
            p = max(1, around - rnd.next(0, min(around - 1, 1200)));
        }
        int a = rnd.next(1, 1000);
        bonuses.push_back({k, {p, a}});
    }
    shuffle(bonuses.begin(), bonuses.end());

    println(n, b);
    for (const auto& bonus : bonuses) {
        println(bonus.first, bonus.second.first, bonus.second.second);
    }
    for (const auto& row : skill) {
        println(row);
    }

    return 0;
}
