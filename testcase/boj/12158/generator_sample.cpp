#include "testlib.h"
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

struct Group {
    int d;
    int h;
    long long m;
};

bool addGroup(vector<Group>& groups, set<pair<int, long long>>& seen, int d, int h, long long m) {
    vector<pair<int, long long>> hikers;
    for (int offset = 0; offset < h; ++offset) {
        hikers.push_back({d, m + offset});
        if (seen.count(hikers.back())) return false;
    }

    for (const auto& hiker : hikers) seen.insert(hiker);
    groups.push_back({d, h, m});
    return true;
}

int pickDegree(int mode) {
    if (mode == 0) return rnd.any(vector<int>{1, 2, 3, 357, 358, 359});
    if (mode == 1) return rnd.any(vector<int>{90, 120, 180, 240, 270});
    return rnd.next(1, 359);
}

long long pickRevolutionTime(int mode) {
    if (mode == 0) return rnd.any(vector<long long>{1, 2, 3, 4, 5});
    if (mode == 1) return rnd.any(vector<long long>{999999991LL, 999999995LL, 999999999LL, 1000000000LL});
    if (mode == 2) return rnd.next(1, 20);
    return rnd.next(1LL, 1000000000LL);
}

vector<Group> makeCase() {
    vector<Group> groups;
    set<pair<int, long long>> seen;

    int mode = rnd.next(0, 5);
    int targetHikers = rnd.next(1, 10);
    int speedMode = rnd.next(0, 3);

    if (mode == 0) {
        int h = targetHikers;
        int d = pickDegree(1);
        long long m = min(1000000000LL - h + 1, pickRevolutionTime(speedMode));
        addGroup(groups, seen, d, h, m);
        return groups;
    }

    if (mode == 1) {
        long long m = pickRevolutionTime(speedMode);
        for (int i = 0; i < targetHikers; ++i) {
            int d = 1 + (i * 358 / max(1, targetHikers - 1));
            addGroup(groups, seen, d, 1, m);
        }
        shuffle(groups.begin(), groups.end());
        return groups;
    }

    while ((int)seen.size() < targetHikers) {
        int remaining = targetHikers - (int)seen.size();
        int d = pickDegree(mode == 2 ? 0 : rnd.next(0, 2));
        int h = rnd.next(1, min(remaining, 4));
        long long m = pickRevolutionTime(speedMode);
        if (m + h - 1 > 1000000000LL) m = 1000000000LL - h + 1;

        if (mode == 2 && !groups.empty() && rnd.next(0, 1)) d = groups[0].d;
        if (!addGroup(groups, seen, d, h, m)) {
            addGroup(groups, seen, pickDegree(2), 1, rnd.next(1LL, 1000000000LL));
        }
    }

    shuffle(groups.begin(), groups.end());
    return groups;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 12);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        vector<Group> groups = makeCase();
        println((int)groups.size());
        for (const Group& group : groups) {
            println(group.d, group.h, group.m);
        }
    }

    return 0;
}
