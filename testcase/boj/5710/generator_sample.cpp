#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

long long bill(long long usage) {
    long long total = 0;

    long long take = min(usage, 100LL);
    total += take * 2;
    usage -= take;

    take = min(usage, 9900LL);
    total += take * 3;
    usage -= take;

    take = min(usage, 990000LL);
    total += take * 5;
    usage -= take;

    total += usage * 7;
    return total;
}

long long randomUsageNear(long long center, long long radius) {
    long long lo = max(1LL, center - radius);
    long long hi = min(120000000LL, center + radius);
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<long long, long long>> cases;
    int caseCount = rnd.next(8, 18);

    vector<long long> anchors = {
        1, 2, 50, 99, 100, 101, 150, 500,
        9999, 10000, 10001, 15000, 500000,
        999999, 1000000, 1000001, 2000000, 120000000
    };

    while ((int)cases.size() < caseCount) {
        int mode = rnd.next(0, 5);
        long long mine;
        long long neighbor;

        if (mode == 0) {
            mine = rnd.next(1LL, 100LL);
            neighbor = rnd.next(mine + 1, 250LL);
        } else if (mode == 1) {
            mine = randomUsageNear(rnd.any(anchors), rnd.next(0LL, 80LL));
            neighbor = mine + rnd.next(1LL, 400LL);
        } else if (mode == 2) {
            mine = rnd.next(1LL, 20000LL);
            neighbor = rnd.next(mine + 1, min(1000000LL, mine + rnd.next(1LL, 80000LL)));
        } else if (mode == 3) {
            mine = randomUsageNear(1000000LL, rnd.next(0LL, 200000LL));
            neighbor = mine + rnd.next(1LL, 3000000LL);
        } else if (mode == 4) {
            mine = rnd.next(1LL, 1000000LL);
            neighbor = rnd.next(mine + 1, 120000000LL);
        } else {
            mine = rnd.next(1LL, 70000000LL);
            neighbor = mine + rnd.next(1LL, 50000000LL);
            neighbor = min(neighbor, 120000000LL);
            if (neighbor <= mine) {
                neighbor = mine + 1;
            }
        }

        long long a = bill(mine + neighbor);
        long long b = bill(neighbor) - bill(mine);
        if (1 <= a && a <= 1000000000LL && 1 <= b && b <= 1000000000LL) {
            cases.push_back({a, b});
        }
    }

    shuffle(cases.begin(), cases.end());
    for (auto [a, b] : cases) {
        println(a, b);
    }
    println(0, 0);

    return 0;
}
