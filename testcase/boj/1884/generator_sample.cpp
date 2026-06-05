#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

struct Road {
    int s;
    int d;
    int l;
    int t;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 12);
    int k = rnd.next(0, 40);
    vector<Road> roads;

    auto addRoad = [&](int s, int d, int l, int t) {
        roads.push_back({s, d, l, t});
    };

    auto addRandomRoad = [&]() {
        addRoad(rnd.next(1, n), rnd.next(1, n), rnd.next(1, 30), rnd.next(0, 30));
    };

    if (mode == 0) {
        int chainLength = rnd.next(1, min(n - 1, 5));
        int totalToll = 0;
        for (int i = 1; i <= chainLength; ++i) {
            int s = i;
            int d = (i == chainLength ? n : i + 1);
            int toll = rnd.next(0, max(0, min(10, k - totalToll)));
            totalToll += toll;
            addRoad(s, d, rnd.next(1, 20), toll);
        }
    } else if (mode == 1) {
        k = rnd.next(0, 12);
        addRoad(1, n, rnd.next(1, 10), k + rnd.next(1, 20));
        if (n > 2) {
            addRoad(1, 2, rnd.next(1, 10), rnd.next(0, k));
            addRoad(2, n, rnd.next(1, 10), k + rnd.next(1, 20));
        }
    } else if (mode == 2) {
        int directToll = rnd.next(0, k);
        addRoad(1, n, rnd.next(15, 40), directToll);
        int mid = rnd.next(2, n - 1);
        int firstToll = rnd.next(0, k);
        int secondToll = rnd.next(0, max(0, k - firstToll));
        addRoad(1, mid, rnd.next(1, 10), firstToll);
        addRoad(mid, n, rnd.next(1, 10), secondToll);
        addRoad(1, n, rnd.next(1, 8), k + rnd.next(1, 10));
    } else if (mode == 3) {
        k = rnd.next(0, 25);
        int toll = rnd.next(0, k);
        int len = rnd.next(1, 30);
        addRoad(1, n, len, toll);
        addRoad(1, n, max(1, len - rnd.next(0, 5)), min(100, toll + rnd.next(0, 5)));
        addRoad(1, n, rnd.next(1, 30), k + rnd.next(1, 20));
    } else if (mode == 4) {
        k = 0;
        for (int i = 1; i < n; ++i) {
            addRoad(i, i + 1, rnd.next(1, 12), 0);
        }
    } else {
        if (n > 2) {
            addRoad(1, 2, rnd.next(1, 20), rnd.next(0, min(20, k)));
            addRoad(2, 2, rnd.next(1, 20), rnd.next(0, 20));
        } else {
            addRoad(1, 1, rnd.next(1, 20), rnd.next(0, 20));
        }
    }

    int extra = rnd.next(0, 18);
    for (int i = 0; i < extra; ++i) {
        if (rnd.next(0, 4) == 0 && !roads.empty()) {
            Road base = rnd.any(roads);
            addRoad(base.s, base.d, rnd.next(1, 30), rnd.next(0, 30));
        } else {
            addRandomRoad();
        }
    }

    shuffle(roads.begin(), roads.end());

    println(k);
    println(n);
    println(static_cast<int>(roads.size()));
    for (const Road& road : roads) {
        println(road.s, road.d, road.l, road.t);
    }

    return 0;
}
