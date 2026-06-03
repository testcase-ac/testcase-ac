#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<pair<int, int>> jobs;

    if (mode == 0) {
        jobs.push_back({rnd.next(1, 1000), rnd.next(1, 10000)});
    } else if (mode == 1) {
        int n = rnd.next(2, 18);
        int baseT = rnd.next(1, 80);
        int baseS = rnd.next(1, 120);
        int maxK = min(1000 / baseT, 10000 / baseS);
        maxK = max(1, maxK);
        for (int i = 0; i < n; ++i) {
            int k = rnd.next(1, maxK);
            jobs.push_back({baseT * k, baseS * k});
        }
    } else if (mode == 2) {
        int n = rnd.next(6, 24);
        int centerT = rnd.next(2, 50);
        int centerS = rnd.next(2, 500);
        for (int i = 0; i < n; ++i) {
            int t = min(1000, max(1, centerT + rnd.next(-2, 2)));
            int s = min(10000, max(1, centerS + rnd.next(-20, 20)));
            jobs.push_back({t, s});
        }
    } else if (mode == 3) {
        int n = rnd.next(8, 35);
        for (int i = 0; i < n; ++i) {
            int t;
            if (rnd.next(0, 3) == 0) {
                t = rnd.any(vector<int>{1, 2, 999, 1000});
            } else {
                t = rnd.next(1, 1000);
            }
            int s;
            if (rnd.next(0, 3) == 0) {
                s = rnd.any(vector<int>{1, 2, 9999, 10000});
            } else {
                s = rnd.next(1, 10000);
            }
            jobs.push_back({t, s});
        }
    } else if (mode == 4) {
        int n = rnd.next(5, 28);
        for (int i = 0; i < n; ++i) {
            int t = rnd.next(1, 25);
            int s = rnd.next(1, 25);
            if (rnd.next(0, 4) == 0) {
                s *= rnd.next(10, 400);
            }
            jobs.push_back({t, min(s, 10000)});
        }
    } else {
        int n = rnd.next(10, 50);
        int highPenaltyCount = rnd.next(1, n);
        for (int i = 0; i < n; ++i) {
            if (i < highPenaltyCount) {
                jobs.push_back({rnd.next(1, 30), rnd.next(5000, 10000)});
            } else {
                jobs.push_back({rnd.next(200, 1000), rnd.next(1, 200)});
            }
        }
    }

    shuffle(jobs.begin(), jobs.end());

    println(static_cast<int>(jobs.size()));
    for (const auto& job : jobs) {
        println(job.first, job.second);
    }

    return 0;
}
