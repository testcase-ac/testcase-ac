#include "testlib.h"

#include <numeric>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxCoord = 100000000;

    vector<pair<int, int>> candidates;

    int mode = rnd.next(0, 7);
    if (mode == 0) {
        candidates.push_back({0, 0});
        candidates.push_back({rnd.next(0, 1), rnd.next(0, 30)});
        candidates.push_back({rnd.next(0, 30), rnd.next(0, 1)});
    } else if (mode == 1) {
        int x = rnd.next(0, 1);
        int y = rnd.next(maxCoord - 100, maxCoord);
        candidates.push_back({x, y});
    } else if (mode == 2) {
        int x = rnd.next(maxCoord - 100, maxCoord);
        int y = rnd.next(0, 1);
        candidates.push_back({x, y});
    } else if (mode == 3) {
        int x = rnd.next(2, 30);
        int y = rnd.next(2, 30);
        while (gcd(x, y) != 1) {
            x = rnd.next(2, 30);
            y = rnd.next(2, 30);
        }
        candidates.push_back({x, y});
    } else if (mode == 4) {
        int base = rnd.next(2, 1000);
        int delta = rnd.next(1, 25);
        candidates.push_back({base, base + delta});
        candidates.push_back({base + delta, base});
    } else if (mode == 5) {
        int x = rnd.next(maxCoord - 5000, maxCoord);
        int y = rnd.next(maxCoord - 5000, maxCoord);
        while (gcd(x, y) != 1) {
            x = rnd.next(maxCoord - 5000, maxCoord);
            y = rnd.next(maxCoord - 5000, maxCoord);
        }
        candidates.push_back({x, y});
    } else if (mode == 6) {
        int x = rnd.next(2, 100);
        int y = rnd.next(2, 100);
        while (gcd(x, y) != 1 || x == y) {
            x = rnd.next(2, 100);
            y = rnd.next(2, 100);
        }
        candidates.push_back({x, y});
    } else {
        candidates.push_back({6, 5});
        candidates.push_back({maxCoord, maxCoord - 1});
        candidates.push_back({rnd.next(2, 50), 1});
        candidates.push_back({1, rnd.next(2, 50)});
    }

    auto point = rnd.any(candidates);
    if (rnd.next(0, 1)) {
        swap(point.first, point.second);
    }

    println(point.first, point.second);
    return 0;
}
