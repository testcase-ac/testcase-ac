#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Group {
    int d;
    int h;
    int m;
};

int choosePeriod() {
    int mode = rnd.next(5);
    if (mode == 0) return 1;
    if (mode == 1) return rnd.next(2, 6);
    if (mode == 2) return rnd.next(7, 30);
    if (mode == 3) return rnd.next(999999990, 1000000000);
    return rnd.next(1, 1000000000);
}

int chooseDegree() {
    int mode = rnd.next(5);
    if (mode == 0) return 1;
    if (mode == 1) return 180;
    if (mode == 2) return 359;
    return rnd.next(1, 359);
}

bool hasDuplicateHiker(const vector<Group>& groups) {
    set<pair<int, long long>> hikers;
    for (const Group& group : groups) {
        for (int offset = 0; offset < group.h; ++offset) {
            if (!hikers.insert({group.d, static_cast<long long>(group.m) + offset}).second) {
                return true;
            }
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 12);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        vector<Group> groups;
        int mode = rnd.next(4);

        if (mode == 0) {
            groups.push_back({chooseDegree(), 1, choosePeriod()});
        } else if (mode == 1) {
            groups.push_back({chooseDegree(), 2, rnd.next(1, 999999999)});
        } else if (mode == 2) {
            int d = chooseDegree();
            int m1 = choosePeriod();
            int m2 = choosePeriod();
            if (m1 == m2) {
                m2 = (m2 == 1000000000 ? 999999999 : m2 + 1);
            }
            groups.push_back({d, 1, m1});
            groups.push_back({d, 1, m2});
        } else {
            groups.push_back({chooseDegree(), 1, choosePeriod()});
            groups.push_back({chooseDegree(), 1, choosePeriod()});
        }

        while (hasDuplicateHiker(groups)) {
            for (Group& group : groups) {
                group.d = chooseDegree();
                group.m = choosePeriod();
                if (group.h == 2 && group.m == 1000000000) {
                    group.m = 999999999;
                }
            }
        }

        shuffle(groups.begin(), groups.end());
        println(static_cast<int>(groups.size()));
        for (const Group& group : groups) {
            println(group.d, group.h, group.m);
        }
    }

    return 0;
}
