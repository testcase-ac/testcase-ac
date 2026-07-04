#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

namespace {

const long long kMinValue = -1000000000LL;
const long long kMaxValue = 1000000000LL;

long long randomNonZero(long long lo, long long hi) {
    long long value = rnd.next(lo, hi);
    if (value == 0) value = rnd.next(0, 1) == 0 ? -1 : 1;
    return value;
}

void addUnique(set<long long>& used, vector<long long>& values, long long value) {
    if (value == 0 || value < kMinValue || value > kMaxValue) return;
    if (used.insert(value).second) values.push_back(value);
}

void fillRandom(set<long long>& used, vector<long long>& values, int n, long long lo, long long hi) {
    while ((int)values.size() < n) {
        addUnique(used, values, randomNonZero(lo, hi));
    }
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 18);
    int mode = rnd.next(0, 5);

    vector<long long> values;
    set<long long> used;

    if (mode == 0) {
        fillRandom(used, values, n, -20, 20);
    } else if (mode == 1) {
        fillRandom(used, values, n, 1, 60);
    } else if (mode == 2) {
        fillRandom(used, values, n, -60, -1);
    } else if (mode == 3) {
        long long x = rnd.next(1, 100);
        addUnique(used, values, -x);
        addUnique(used, values, x + rnd.next(-2, 2));
        fillRandom(used, values, n, -150, 150);
    } else if (mode == 4) {
        addUnique(used, values, -1000000000LL);
        addUnique(used, values, 1000000000LL);
        fillRandom(used, values, n, -1000, 1000);
    } else {
        int negatives = rnd.next(1, n - 1);
        fillRandom(used, values, negatives, -80, -1);
        fillRandom(used, values, n, 1, 80);
    }

    shuffle(values.begin(), values.end());

    println(n);
    println(values);

    return 0;
}
