#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Door {
    int a;
    int b;
    long long c;
    long long d;
};

long long pickK() {
    if (rnd.next(4) == 0) {
        return rnd.next(1000000LL, 1000000000LL);
    }
    return rnd.next(1LL, 80LL);
}

pair<long long, long long> randomInterval(long long k) {
    long long c = rnd.next(1LL, k);
    long long d = rnd.next(c, k);
    return {c, d};
}

void addDoor(vector<Door>& doors, set<pair<int, int>>& used, int a, int b,
             long long c, long long d) {
    if (a == b || used.count({a, b})) {
        return;
    }
    used.insert({a, b});
    doors.push_back({a, b, c, d});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int n = rnd.next(2, 12);
    long long k = pickK();
    int s = rnd.next(1, n);
    int t = rnd.next(1, n - 1);
    if (t >= s) {
        ++t;
    }

    vector<Door> doors;
    set<pair<int, int>> used;

    if (mode == 0) {
        addDoor(doors, used, s, t, 1, k);
    } else {
        vector<int> middle;
        for (int v = 1; v <= n; ++v) {
            if (v != s && v != t) {
                middle.push_back(v);
            }
        }
        shuffle(middle.begin(), middle.end());

        int pathEdges = min<int>(rnd.next(1, 4), n - 1);
        vector<int> path = {s};
        for (int i = 0; i + 1 < pathEdges && i < (int)middle.size(); ++i) {
            path.push_back(middle[i]);
        }
        path.push_back(t);

        long long baseL = rnd.next(1LL, k);
        long long baseR = rnd.next(baseL, k);
        if (mode == 2 && baseL < baseR) {
            long long mid = rnd.next(baseL, baseR - 1);
            for (int i = 0; i + 1 < (int)path.size(); ++i) {
                if (i % 2 == 0) {
                    addDoor(doors, used, path[i], path[i + 1], baseL, mid);
                } else {
                    addDoor(doors, used, path[i], path[i + 1], mid + 1, baseR);
                }
            }
        } else {
            for (int i = 0; i + 1 < (int)path.size(); ++i) {
                long long slackL = rnd.next(0LL, baseL - 1);
                long long slackR = rnd.next(0LL, k - baseR);
                addDoor(doors, used, path[i], path[i + 1], baseL - slackL,
                        baseR + slackR);
            }
        }
    }

    vector<pair<int, int>> candidates;
    for (int a = 1; a <= n; ++a) {
        for (int b = 1; b <= n; ++b) {
            if (a != b && !used.count({a, b})) {
                candidates.push_back({a, b});
            }
        }
    }
    shuffle(candidates.begin(), candidates.end());

    int extraLimit = mode == 3 ? min<int>(35, candidates.size())
                               : min<int>(14, candidates.size());
    int extras = rnd.next(0, extraLimit);
    for (int i = 0; i < extras; ++i) {
        auto [c, d] = randomInterval(k);
        addDoor(doors, used, candidates[i].first, candidates[i].second, c, d);
    }

    if (doors.empty()) {
        addDoor(doors, used, s, t, 1, k);
    }

    shuffle(doors.begin(), doors.end());

    println(n, (int)doors.size(), k);
    println(s, t);
    for (const Door& door : doors) {
        println(door.a, door.b, door.c, door.d);
    }

    return 0;
}
