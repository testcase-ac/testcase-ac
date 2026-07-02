#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>
using namespace std;

bool canRemoveDistances(const multiset<long long>& distances,
                        const vector<long long>& positions,
                        long long x,
                        vector<long long>& removed) {
    multiset<long long> remaining = distances;
    removed.clear();

    for (long long p : positions) {
        long long d = llabs(x - p);
        auto it = remaining.find(d);
        if (it == remaining.end()) {
            return false;
        }
        remaining.erase(it);
        removed.push_back(d);
    }
    return true;
}

bool restorePossible(multiset<long long>& distances,
                     vector<long long>& positions,
                     int n,
                     long long width) {
    if (static_cast<int>(positions.size()) == n) {
        return distances.empty();
    }

    long long largest = *distances.rbegin();
    vector<long long> candidates = {largest, width - largest};

    for (long long x : candidates) {
        if (x <= 0 || x >= width) {
            continue;
        }
        if (find(positions.begin(), positions.end(), x) != positions.end()) {
            continue;
        }

        vector<long long> removed;
        if (!canRemoveDistances(distances, positions, x, removed)) {
            continue;
        }

        for (long long d : removed) {
            auto it = distances.find(d);
            ensuref(it != distances.end(), "internal distance-removal mismatch");
            distances.erase(it);
        }
        positions.push_back(x);

        if (restorePossible(distances, positions, n, width)) {
            return true;
        }

        positions.pop_back();
        for (long long d : removed) {
            distances.insert(d);
        }
    }

    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 20, "n");
    inf.readEoln();

    int m = n * (n - 1) / 2;
    vector<long long> d(m);
    for (int i = 0; i < m; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        d[i] = inf.readLong(1LL, 1000000000LL, "d_i");
        if (i > 0) {
            ensuref(d[i - 1] <= d[i],
                    "distances must be sorted: d[%d]=%lld, d[%d]=%lld",
                    i, d[i - 1], i + 1, d[i]);
        }
    }
    inf.readEoln();
    inf.readEof();

    if (n == 2) {
        return 0;
    }

    long long width = d.back();
    multiset<long long> distances(d.begin(), d.end());
    auto it = distances.find(width);
    ensuref(it != distances.end(), "missing maximum distance");
    distances.erase(it);

    vector<long long> positions = {0, width};
    ensuref(restorePossible(distances, positions, n, width),
            "distances cannot be realized by strictly increasing house positions");
}
