#include "testlib.h"

#include <algorithm>
#include <map>
#include <utility>
#include <vector>

using namespace std;

struct Group {
    int d;
    int h;
    long long m;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int n = rnd.next(1, mode == 5 ? 14 : 9);
        vector<Group> groups;
        map<int, vector<pair<long long, long long>>> used;

        auto addGroup = [&](int d, int h, long long m) {
            groups.push_back({d, h, m});
            used[d].push_back({m, m + h - 1});
        };

        auto fits = [&](int d, int h, long long m) {
            long long r = m + h - 1;
            for (auto interval : used[d]) {
                if (!(r < interval.first || interval.second < m)) {
                    return false;
                }
            }
            return true;
        };

        for (int i = 0; i < n; ++i) {
            int d;
            if (mode == 0) {
                d = rnd.any(vector<int>{1, 2, 180, 358, 359});
            } else if (mode == 1) {
                d = rnd.any(vector<int>{90, 180, 270});
            } else if (mode == 2) {
                d = rnd.next(1, 25);
            } else if (mode == 3) {
                d = rnd.next(335, 359);
            } else {
                d = rnd.next(1, 359);
            }

            int h;
            if (mode == 4 && i == 0) {
                h = rnd.next(20, 80);
            } else if (mode == 5) {
                h = rnd.next(1, 8);
            } else {
                h = rnd.next(1, 4);
            }

            long long m;
            if (mode == 0) {
                m = rnd.any(vector<long long>{1, 2, 3, 10, 1000000000LL});
            } else if (mode == 3) {
                m = rnd.next(1, 12);
            } else if (mode == 4) {
                m = rnd.next(999999900LL, 1000000000LL - h + 1);
            } else {
                m = rnd.next(1, 200);
            }

            int attempts = 0;
            while (!fits(d, h, m) && attempts < 200) {
                if (mode == 1) {
                    m = 1 + 10LL * (i + 1) + rnd.next(0, 5);
                } else if (mode == 4) {
                    m = rnd.next(999999000LL, 1000000000LL - h + 1);
                } else {
                    m = rnd.next(1, 1000);
                }
                ++attempts;
            }

            if (!fits(d, h, m)) {
                d = rnd.next(1, 359);
                h = 1;
                m = 1000LL + i;
                while (!fits(d, h, m)) {
                    d = d % 359 + 1;
                    ++m;
                }
            }

            addGroup(d, h, m);
        }

        shuffle(groups.begin(), groups.end());
        println((int)groups.size());
        for (const Group& group : groups) {
            println(group.d, group.h, group.m);
        }
    }

    return 0;
}
