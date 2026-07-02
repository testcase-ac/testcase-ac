#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

const long long LIM = 1000000000LL;

long long pickFromRanges(const vector<pair<long long, long long>>& ranges) {
    vector<pair<long long, long long>> valid;
    for (auto range : ranges) {
        long long lo = max(1LL, range.first);
        long long hi = min(LIM, range.second);
        if (lo <= hi) {
            valid.push_back({lo, hi});
        }
    }
    auto chosen = rnd.any(valid);
    return rnd.next(chosen.first, chosen.second);
}

bool hasValidRange(const vector<pair<long long, long long>>& ranges) {
    for (auto range : ranges) {
        if (max(1LL, range.first) <= min(LIM, range.second)) {
            return true;
        }
    }
    return false;
}

void addHeights(vector<long long>& heights, int count, const vector<pair<long long, long long>>& ranges) {
    if (!hasValidRange(ranges)) {
        return;
    }
    for (int i = 0; i < count; ++i) {
        heights.push_back(pickFromRanges(ranges));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    long long l1, r1, l2, r2;
    int mode = rnd.next(0, 7);
    if (mode == 0) {
        l1 = l2 = rnd.next(1LL, 20LL);
        r1 = r2 = rnd.next(l1, l1 + rnd.next(0LL, 20LL));
    } else if (mode == 1) {
        l1 = rnd.next(1LL, 15LL);
        r1 = rnd.next(l1, l1 + 10LL);
        l2 = rnd.next(r1 + 1LL, r1 + 12LL);
        r2 = rnd.next(l2, l2 + 10LL);
    } else if (mode == 2) {
        l1 = rnd.next(1LL, 15LL);
        r1 = rnd.next(l1 + 2LL, l1 + 18LL);
        l2 = rnd.next(l1 + 1LL, r1);
        r2 = rnd.next(r1, r1 + 18LL);
    } else if (mode == 3) {
        l2 = rnd.next(1LL, 10LL);
        r2 = rnd.next(l2 + 8LL, l2 + 30LL);
        l1 = rnd.next(l2, r2 - 1LL);
        r1 = rnd.next(l1, r2);
    } else if (mode == 4) {
        l1 = rnd.next(1LL, 10LL);
        r1 = rnd.next(l1 + 8LL, l1 + 30LL);
        l2 = rnd.next(l1, r1 - 1LL);
        r2 = rnd.next(l2, r1);
    } else if (mode == 5) {
        l1 = rnd.next(1LL, 8LL);
        r1 = rnd.next(l1, l1 + 3LL);
        l2 = rnd.next(1LL, 8LL);
        r2 = rnd.next(l2, l2 + 3LL);
    } else {
        l1 = rnd.next(999999930LL, 999999960LL);
        r1 = rnd.next(l1, LIM);
        l2 = rnd.next(999999930LL, 999999960LL);
        r2 = rnd.next(l2, LIM);
    }

    if (rnd.next(2)) {
        swap(l1, l2);
        swap(r1, r2);
    }

    vector<pair<long long, long long>> petyaOnly = {{l1, min(r1, l2 - 1)}, {max(l1, r2 + 1), r1}};
    vector<pair<long long, long long>> vasyaOnly = {{l2, min(r2, l1 - 1)}, {max(l2, r1 + 1), r2}};
    vector<pair<long long, long long>> both = {{max(l1, l2), min(r1, r2)}};
    vector<pair<long long, long long>> neither = {{1, min(l1, l2) - 1}, {max(r1, r2) + 1, LIM}};

    vector<long long> heights;
    addHeights(heights, rnd.next(0, 8), petyaOnly);
    addHeights(heights, rnd.next(0, 8), vasyaOnly);
    addHeights(heights, rnd.next(0, 10), both);
    addHeights(heights, rnd.next(0, 6), neither);

    vector<long long> boundaries = {l1, r1, l2, r2};
    shuffle(boundaries.begin(), boundaries.end());
    int boundaryCount = rnd.next(0, min(4, (int)boundaries.size()));
    for (int i = 0; i < boundaryCount; ++i) {
        heights.push_back(boundaries[i]);
    }

    if (heights.empty()) {
        heights.push_back(rnd.any(boundaries));
    }

    shuffle(heights.begin(), heights.end());

    int n = (int)heights.size();
    int m;
    if (rnd.next(4) == 0) {
        m = n;
    } else {
        m = rnd.next(1, n);
    }

    println(n, m);
    println(l1, r1);
    println(l2, r2);
    println(heights);

    return 0;
}
