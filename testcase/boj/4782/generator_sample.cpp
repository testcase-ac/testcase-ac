#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

namespace {

constexpr int kMaxValue = 1000000;

void addUnique(vector<pair<int, int>>& cases, int b, int n) {
    b = max(1, min(kMaxValue, b));
    n = max(1, min(kMaxValue, n));
    pair<int, int> candidate = {b, n};
    if (find(cases.begin(), cases.end(), candidate) == cases.end()) {
        cases.push_back(candidate);
    }
}

int nearbyPositive(int center, int radius) {
    return max(1, min(kMaxValue, center + rnd.next(-radius, radius)));
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> cases;
    int targetCases = rnd.next(10, 24);

    addUnique(cases, rnd.next(1, 12), rnd.next(1, 12));
    addUnique(cases, rnd.next(1, 40), rnd.next(1, 40));
    addUnique(cases, rnd.next(1, 200), rnd.next(1, 200));

    int equal = rnd.next(1, 1000);
    addUnique(cases, equal, equal);

    int scale = rnd.next(1, 200);
    int baseB = rnd.next(1, 40);
    int baseN = rnd.next(1, 40);
    addUnique(cases, baseB * scale, baseN * scale);

    int n = rnd.next(2, 500);
    addUnique(cases, rnd.next(1, n), n);
    addUnique(cases, nearbyPositive(n, 3), n);

    addUnique(cases, 1, rnd.next(1, kMaxValue));
    addUnique(cases, rnd.next(1, kMaxValue), 1);
    addUnique(cases, kMaxValue, rnd.next(kMaxValue - 1000, kMaxValue));
    addUnique(cases, rnd.next(kMaxValue - 1000, kMaxValue), kMaxValue);

    while ((int)cases.size() < targetCases) {
        int mode = rnd.next(0, 5);
        if (mode == 0) {
            addUnique(cases, rnd.next(1, 60), rnd.next(1, 60));
        } else if (mode == 1) {
            int g = rnd.next(2, 500);
            addUnique(cases, rnd.next(1, 2000 / g) * g, rnd.next(1, 2000 / g) * g);
        } else if (mode == 2) {
            int value = rnd.next(1, kMaxValue);
            addUnique(cases, value, nearbyPositive(value, 20));
        } else if (mode == 3) {
            int large = rnd.next(kMaxValue - 5000, kMaxValue);
            addUnique(cases, rnd.next(1, kMaxValue), large);
        } else if (mode == 4) {
            int large = rnd.next(kMaxValue - 5000, kMaxValue);
            addUnique(cases, large, rnd.next(1, kMaxValue));
        } else {
            addUnique(cases, rnd.next(1, kMaxValue), rnd.next(1, kMaxValue));
        }
    }

    shuffle(cases.begin(), cases.end());

    for (auto [b, n] : cases) {
        println(b, n);
    }
    println(0, 0);

    return 0;
}
