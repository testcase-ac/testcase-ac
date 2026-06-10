#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Case {
    long long x;
    long long y;
    vector<int> a;
};

long long subsetSum(const vector<int>& a, int mask) {
    long long sum = 0;
    for (int i = 0; i < 5; ++i) {
        if (mask & (1 << i)) {
            sum += a[i];
        }
    }
    return sum;
}

vector<long long> subsetSums(const vector<int>& a) {
    vector<long long> sums;
    for (int mask = 0; mask < (1 << 5); ++mask) {
        sums.push_back(subsetSum(a, mask));
    }
    sort(sums.begin(), sums.end());
    sums.erase(unique(sums.begin(), sums.end()), sums.end());
    return sums;
}

vector<int> randomWeights(int lo, int hi) {
    vector<int> a(5);
    for (int& value : a) {
        value = rnd.next(lo, hi);
    }
    shuffle(a.begin(), a.end());
    return a;
}

Case makeYesCase() {
    vector<int> a = randomWeights(1, rnd.next(20, 100000000));
    int mask = rnd.next(1, (1 << 5) - 1);
    long long sum = subsetSum(a, mask);
    long long x = rnd.next(1LL, sum);
    long long y = rnd.next(sum, min(1000000000LL, sum + rnd.next(0, 50)));
    return {x, y, a};
}

Case makeExactBoundaryCase() {
    vector<int> a = randomWeights(1, 20000000);
    int mask = rnd.next(1, (1 << 5) - 1);
    long long sum = subsetSum(a, mask);
    return {sum, sum, a};
}

Case makeAboveTotalNoCase() {
    vector<int> a = randomWeights(1, rnd.next(10, 1000000));
    long long total = subsetSum(a, (1 << 5) - 1);
    long long x = min(1000000000LL, total + rnd.next(1, 1000));
    long long y = rnd.next(x, min(1000000000LL, x + rnd.next(0, 1000)));
    return {x, y, a};
}

Case makeGapNoCase() {
    for (int attempt = 0; attempt < 100; ++attempt) {
        vector<int> a = randomWeights(1, 60);
        vector<long long> sums = subsetSums(a);
        vector<int> candidates;
        for (int i = 0; i + 1 < int(sums.size()); ++i) {
            if (sums[i] + 1 < sums[i + 1]) {
                candidates.push_back(i);
            }
        }
        if (!candidates.empty()) {
            int index = rnd.any(candidates);
            long long x = sums[index] + 1;
            long long y = rnd.next(x, sums[index + 1] - 1);
            return {x, y, a};
        }
    }
    return makeAboveTotalNoCase();
}

Case makeLargeLimitCase() {
    vector<int> a = randomWeights(90000000, 100000000);
    int mode = rnd.next(0, 2);
    if (mode == 0) {
        long long total = subsetSum(a, (1 << 5) - 1);
        long long y = rnd.next(total, 1000000000LL);
        return {total, y, a};
    }
    long long x = rnd.next(500000001LL, 1000000000LL);
    long long y = rnd.next(x, 1000000000LL);
    return {x, y, a};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(20, 45);
    vector<Case> cases;
    cases.reserve(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 4);
        if (mode == 0) {
            cases.push_back(makeYesCase());
        } else if (mode == 1) {
            cases.push_back(makeExactBoundaryCase());
        } else if (mode == 2) {
            cases.push_back(makeAboveTotalNoCase());
        } else if (mode == 3) {
            cases.push_back(makeGapNoCase());
        } else {
            cases.push_back(makeLargeLimitCase());
        }
    }

    println(t);
    for (const Case& current : cases) {
        println(current.x, current.y);
        println(current.a);
    }

    return 0;
}
