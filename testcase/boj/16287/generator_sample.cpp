#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

namespace {

constexpr int kMinW = 10;
constexpr int kMaxW = 799994;
constexpr int kMinA = 1;
constexpr int kMaxA = 200000;

void addUnique(vector<int>& values, set<int>& used, int value) {
    if (value < kMinA || value > kMaxA || used.count(value)) {
        return;
    }
    values.push_back(value);
    used.insert(value);
}

int freshValue(set<int>& used, int lo, int hi) {
    while (true) {
        int value = rnd.next(lo, hi);
        if (!used.count(value)) {
            used.insert(value);
            return value;
        }
    }
}

vector<int> makeGuaranteedYes(int w, int n) {
    set<int> used;
    vector<int> values;

    while (values.size() < 4) {
        used.clear();
        values.clear();
        int a = rnd.next(1, max(1, w / 4));
        int b = rnd.next(1, max(1, w / 3));
        int c = rnd.next(1, max(1, w / 2));
        int d = w - a - b - c;

        addUnique(values, used, a);
        addUnique(values, used, b);
        addUnique(values, used, c);
        addUnique(values, used, d);
    }

    int flavor = rnd.next(0, 2);
    while ((int)values.size() < n) {
        int candidate;
        if (flavor == 0) {
            candidate = rnd.next(1, min(kMaxA, max(1, w + 30)));
        } else if (flavor == 1) {
            candidate = rnd.next(max(1, w / 2 - 50), min(kMaxA, w / 2 + 50));
        } else {
            candidate = rnd.next(1, kMaxA);
        }
        addUnique(values, used, candidate);
    }

    return values;
}

vector<int> makeImpossibleSmallSum(int w, int n) {
    set<int> used;
    vector<int> values;
    int lo = min(kMaxA - n + 1, max(1, w / 4 + 1));
    for (int value = lo; (int)values.size() < n; ++value) {
        addUnique(values, used, value);
    }
    return values;
}

vector<int> makeSmallDistinct(int n, int maxValue) {
    vector<int> values(maxValue);
    iota(values.begin(), values.end(), 1);
    shuffle(values.begin(), values.end());
    values.resize(n);
    return values;
}

vector<int> makeMixed(int n) {
    set<int> used;
    vector<int> values;
    int hi = rnd.next(n + 10, min(kMaxA, n + 300));
    while ((int)values.size() < n) {
        values.push_back(freshValue(used, 1, hi));
    }
    return values;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n = rnd.next(4, 45);
    int w;
    vector<int> values;

    if (mode == 0) {
        w = rnd.next(kMinW, 260);
        values = makeGuaranteedYes(w, n);
    } else if (mode == 1) {
        w = rnd.next(kMinW, 240);
        values = makeImpossibleSmallSum(w, n);
    } else if (mode == 2) {
        int maxValue = rnd.next(max(n, 12), max(n, 70));
        values = makeSmallDistinct(n, maxValue);
        int base = values[0] + values[1] + values[2] + values[3];
        w = min(kMaxW, max(kMinW, base + rnd.next(-2, 2)));
    } else {
        values = makeMixed(n);
        w = rnd.next(kMinW, min(kMaxW, 4 * (n + 300)));
    }

    shuffle(values.begin(), values.end());
    println(w, n);
    println(values);
    return 0;
}
