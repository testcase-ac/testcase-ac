#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

namespace {

const int kMaxA = 100000;

void appendDistinct(vector<int>& a, int value) {
    if (0 <= value && value <= kMaxA && find(a.begin(), a.end(), value) == a.end()) {
        a.push_back(value);
    }
}

void fillRandomDistinct(vector<int>& a, int n, int lo, int hi) {
    set<int> used(a.begin(), a.end());
    while ((int)a.size() < n) {
        int value = rnd.next(lo, hi);
        if (used.insert(value).second) {
            a.push_back(value);
        }
    }
}

vector<int> forcedYesCase(int n) {
    vector<int> a;
    int base = rnd.next(0, 60000);
    int x = rnd.next(1, 4095);
    int y = rnd.next(1, 4095);

    appendDistinct(a, base);
    appendDistinct(a, base ^ x);
    appendDistinct(a, base ^ y);
    appendDistinct(a, base ^ x ^ y);

    while ((int)a.size() < 4) {
        a.clear();
        base = rnd.next(0, 60000);
        x = rnd.next(1, 4095);
        y = rnd.next(1, 4095);
        appendDistinct(a, base);
        appendDistinct(a, base ^ x);
        appendDistinct(a, base ^ y);
        appendDistinct(a, base ^ x ^ y);
    }

    fillRandomDistinct(a, n, 0, kMaxA);
    shuffle(a.begin(), a.end());
    return a;
}

vector<int> powerLikeCase(int n) {
    vector<int> candidates;
    candidates.push_back(0);
    for (int bit = 0; bit <= 16; ++bit) {
        int value = 1 << bit;
        if (value <= kMaxA) {
            candidates.push_back(value);
        }
    }
    for (int bit = 0; bit <= 15; ++bit) {
        int value = (1 << bit) | (1 << ((bit + 5) % 16));
        if (value <= kMaxA) {
            candidates.push_back(value);
        }
    }
    shuffle(candidates.begin(), candidates.end());

    vector<int> a;
    for (int value : candidates) {
        appendDistinct(a, value);
        if ((int)a.size() == n) {
            break;
        }
    }
    fillRandomDistinct(a, n, 0, kMaxA);
    shuffle(a.begin(), a.end());
    return a;
}

vector<int> highRangeCase(int n) {
    vector<int> a;
    int hi = kMaxA;
    int lo = max(0, hi - rnd.next(30, 250));
    fillRandomDistinct(a, n, lo, hi);
    shuffle(a.begin(), a.end());
    return a;
}

vector<int> lowRangeCase(int n) {
    vector<int> a;
    int hi = max(n + 3, rnd.next(8, 80));
    fillRandomDistinct(a, n, 0, hi);
    shuffle(a.begin(), a.end());
    return a;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(4, 8);
        a = forcedYesCase(n);
    } else if (mode == 1) {
        n = rnd.next(4, 18);
        a = powerLikeCase(n);
    } else if (mode == 2) {
        n = rnd.next(4, 24);
        a = highRangeCase(n);
    } else if (mode == 3) {
        n = rnd.next(4, 28);
        a = lowRangeCase(n);
    } else {
        n = rnd.next(80, 180);
        a.clear();
        fillRandomDistinct(a, n, 0, kMaxA);
        shuffle(a.begin(), a.end());
    }

    println(n);
    println(a);
    return 0;
}
