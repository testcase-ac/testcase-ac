#include "testlib.h"
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

static void addUnique(vector<long long>& beads, set<long long>& used, long long x) {
    if (1 <= x && x <= 1000000000LL && used.insert(x).second) {
        beads.push_back(x);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(3, 24);
    vector<long long> beads;
    set<long long> used;

    if (mode == 0) {
        long long start = rnd.next(1, 1000000000 - n);
        long long step = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            addUnique(beads, used, start + step * i);
        }
    } else if (mode == 1) {
        int lowCount = rnd.next(1, n - 2);
        for (int i = 0; i < lowCount; ++i) {
            addUnique(beads, used, rnd.next(1, 80));
        }
        for (int i = lowCount; i < n; ++i) {
            addUnique(beads, used, 1000000000LL - rnd.next(0, 80));
        }
    } else if (mode == 2) {
        long long center = rnd.next(100, 999999900);
        int radius = rnd.next(n, 120);
        for (int i = 0; i < n; ++i) {
            addUnique(beads, used, center + rnd.next(-radius, radius));
        }
    } else if (mode == 3) {
        addUnique(beads, used, 1);
        addUnique(beads, used, 1000000000LL);
        for (int i = 2; i < n; ++i) {
            addUnique(beads, used, rnd.next(2, 999999999));
        }
    } else if (mode == 4) {
        long long start = rnd.next(1, 999999900);
        for (int i = 0; i < n; ++i) {
            long long offset = 1LL * i * i + rnd.next(0, 3);
            addUnique(beads, used, start + offset);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            addUnique(beads, used, rnd.next(1, 1000000000));
        }
    }

    while ((int)beads.size() < n) {
        addUnique(beads, used, rnd.next(1, 1000000000));
    }

    shuffle(beads.begin(), beads.end());
    println(n);
    println(beads);
    return 0;
}
