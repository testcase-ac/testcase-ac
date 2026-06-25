#include "testlib.h"

#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 100);
    vector<pair<int, int>> cases;
    cases.reserve(t);

    vector<pair<int, int>> anchors = {
        {0, 0},
        {0, rnd.next(0, 10000000)},
        {rnd.next(0, 10000000), 0},
        {10000000, 10000000},
        {rnd.next(1, 30), rnd.next(1, 30)}
    };
    shuffle(anchors.begin(), anchors.end());
    for (auto value : anchors) {
        if ((int)cases.size() < t) {
            cases.push_back(value);
        }
    }

    while ((int)cases.size() < t) {
        int mode = rnd.next(0, 5);
        int n = 0;
        int k = 0;

        if (mode == 0) {
            n = rnd.next(0, 50);
            k = rnd.next(0, 50);
        } else if (mode == 1) {
            n = rnd.next(9999900, 10000000);
            k = rnd.next(0, 100);
        } else if (mode == 2) {
            n = rnd.next(0, 100);
            k = rnd.next(9999900, 10000000);
        } else if (mode == 3) {
            k = rnd.next(1, 1000);
            int quotient = rnd.next(0, 10000);
            int remainder = rnd.next(0, k);
            n = min(10000000, quotient * (k + 1) + remainder);
        } else {
            n = rnd.next(0, 10000000);
            k = rnd.next(0, 10000000);
        }

        cases.push_back({n, k});
    }

    println(t);
    for (auto [n, k] : cases) {
        println(n, k);
    }

    return 0;
}
