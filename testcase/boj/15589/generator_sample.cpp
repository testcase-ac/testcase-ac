#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

const long long MAX_TIME = 1000000000LL;

bool addInterval(vector<pair<long long, long long>>& shifts, set<long long>& used, long long start, long long end) {
    if (start > end) swap(start, end);
    start = max(0LL, min(MAX_TIME, start));
    end = max(0LL, min(MAX_TIME, end));

    if (start < end && !used.count(start) && !used.count(end)) {
        used.insert(start);
        used.insert(end);
        shifts.push_back({start, end});
        return true;
    }

    for (long long delta = 1; delta <= 25; ++delta) {
        long long left = max(0LL, start - delta);
        long long right = min(MAX_TIME, end + delta);
        if (left < right && !used.count(left) && !used.count(right)) {
            used.insert(left);
            used.insert(right);
            shifts.push_back({left, right});
            return true;
        }
    }

    return false;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(1, 12);

    vector<pair<long long, long long>> shifts;
    set<long long> used;

    if (mode == 0) {
        long long cur = rnd.next(0, 8);
        for (int i = 0; i < n; ++i) {
            long long len = rnd.next(1, 8);
            addInterval(shifts, used, cur, cur + len);
            cur += len + rnd.next(1, 6);
        }
    } else if (mode == 1) {
        long long cur = rnd.next(0, 10);
        for (int i = 0; i < n; ++i) {
            long long len = rnd.next(3, 15);
            addInterval(shifts, used, cur, cur + len);
            cur += rnd.next(1, 6);
        }
    } else if (mode == 2) {
        long long base = rnd.next(0, 20);
        long long span = rnd.next(2 * n + 5, 2 * n + 25);
        for (int i = 0; i < n; ++i) {
            addInterval(shifts, used, base + i, base + span - i);
        }
    } else if (mode == 3) {
        long long center = rnd.next(15, 60);
        for (int i = 0; i < n; ++i) {
            long long start = center - rnd.next(1, 14);
            long long end = center + rnd.next(1, 14);
            addInterval(shifts, used, start + 2 * i, end + 3 * i);
        }
    } else {
        vector<pair<long long, long long>> candidates = {
            {0, 1},
            {2, MAX_TIME},
            {3, MAX_TIME - 1},
            {10, 20},
            {11, 19},
            {21, 35},
            {30, 45},
            {46, 50},
            {MAX_TIME - 20, MAX_TIME - 2},
            {MAX_TIME - 19, MAX_TIME - 1},
            {100, 130},
            {120, 150},
        };
        shuffle(candidates.begin(), candidates.end());
        for (int i = 0; i < n; ++i) {
            addInterval(shifts, used, candidates[i].first, candidates[i].second);
        }
    }

    while ((int)shifts.size() < n) {
        long long start = rnd.next(0LL, 200LL);
        long long len = rnd.next(1LL, 30LL);
        if (addInterval(shifts, used, start, start + len)) continue;

        for (long long cur = 0; cur + 1 <= MAX_TIME; cur += 2) {
            if (addInterval(shifts, used, cur, cur + 1)) break;
        }
    }

    shuffle(shifts.begin(), shifts.end());

    println((int)shifts.size());
    for (auto [start, end] : shifts) {
        println(start, end);
    }

    return 0;
}
