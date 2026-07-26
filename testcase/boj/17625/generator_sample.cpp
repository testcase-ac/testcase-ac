#include "testlib.h"
#include <set>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 12);
    int mode = rnd.next(0, 2);
    vector<pair<long long, long long>> points;

    if (mode == 0) {
        long long x = rnd.next(-10, 10);
        long long y = rnd.next(-10, 10);
        int dx = rnd.next(1, 4);
        int dy = rnd.next(-4, 4);
        for (int i = 0; i < n; ++i)
            points.emplace_back(x + dx * i, y + dy * i);
    } else {
        set<pair<long long, long long>> used;
        while (static_cast<int>(points.size()) < n) {
            long long x = mode == 1
                ? rnd.next(-10, 10)
                : (rnd.next(0, 1) ? 1 : -1) * (1000000000LL - rnd.next(0, 20));
            long long y = mode == 1
                ? rnd.next(-10, 10)
                : (rnd.next(0, 1) ? 1 : -1) * (1000000000LL - rnd.next(0, 20));
            pair<long long, long long> point = {x, y};
            if (used.insert(point).second)
                points.push_back(point);
        }
    }

    shuffle(points.begin(), points.end());
    println(n);
    for (const auto& [x, y] : points)
        println(x, y);
}
