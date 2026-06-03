#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = rnd.next(1, 14);
    vector<pair<int, long long>> switches;
    switches.reserve(n);

    auto addSwitch = [&](int ports, long long cost) {
        switches.push_back({ports, cost});
    };

    if (mode == 0) {
        n = 1;
        int ports = rnd.next(2, 12);
        long long cost = rnd.next(0, 30);
        addSwitch(ports, cost);
    } else if (mode == 1) {
        n = rnd.next(1, 10);
        for (int i = 0; i < n; ++i) addSwitch(2, rnd.next(0, 40));
    } else if (mode == 2) {
        n = rnd.next(4, 14);
        int base = rnd.next(2, 8);
        for (int i = 0; i < n; ++i) {
            int ports = base + rnd.next(0, 2);
            long long cost = rnd.next(0, 3) == 0 ? 0 : rnd.next(1, 60);
            addSwitch(ports, cost);
        }
    } else if (mode == 3) {
        n = rnd.next(3, 12);
        for (int i = 0; i < n; ++i) {
            int extra = rnd.next(0, 20);
            long long cost = rnd.next(0, 100);
            addSwitch(extra + 2, cost);
        }
    } else if (mode == 4) {
        n = rnd.next(2, 8);
        for (int i = 0; i < n; ++i) {
            int ports = rnd.next(2, 20);
            long long cost = rnd.next(0, 1) ? 1000000000LL : rnd.next(0, 1000);
            addSwitch(ports, cost);
        }
    } else {
        n = rnd.next(4, 14);
        for (int i = 0; i < n; ++i) {
            int ports = rnd.next(2, 30);
            long long cost = rnd.next(0, 200);
            addSwitch(ports, cost);
        }
    }

    shuffle(switches.begin(), switches.end());

    vector<int> reachable(1, 0);
    int totalExtra = 0;
    for (auto [ports, cost] : switches) {
        (void)cost;
        int extra = ports - 2;
        totalExtra += extra;
        int oldSize = static_cast<int>(reachable.size());
        for (int i = 0; i < oldSize; ++i) reachable.push_back(reachable[i] + extra);
    }
    sort(reachable.begin(), reachable.end());
    reachable.erase(unique(reachable.begin(), reachable.end()), reachable.end());

    int targetExtra = 0;
    if ((mode == 3 || mode == 5) && totalExtra + 1 <= 99999) {
        targetExtra = totalExtra + rnd.next(1, min(8, 99999 - totalExtra));
    } else if (mode == 6) {
        targetExtra = rnd.next(0, min(99999, totalExtra + 10));
    } else {
        targetExtra = rnd.any(reachable);
    }

    int m = targetExtra + 1;

    println(static_cast<int>(switches.size()));
    for (auto [ports, cost] : switches) println(ports, cost);
    println(m);

    return 0;
}
