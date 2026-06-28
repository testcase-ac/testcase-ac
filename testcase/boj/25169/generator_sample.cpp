#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int randomStress() {
    return rnd.next(1, 1000) * 10;
}

void printJobs(const vector<pair<int, int>>& jobs) {
    println(static_cast<int>(jobs.size()));
    for (const auto& job : jobs) {
        println(job.first, job.second);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<pair<int, int>> jobs;

    if (mode == 0) {
        int n = rnd.next(1, 5);
        for (int i = 0; i < n; ++i) {
            jobs.push_back({rnd.next(1, 6), rnd.next(1, 20) * 10});
        }
    } else if (mode == 1) {
        int n = rnd.next(4, 12);
        int baseR = rnd.next(1, 8);
        int baseS = rnd.next(1, 40) * 10;
        for (int i = 0; i < n; ++i) {
            int r = max(1, min(100, baseR + rnd.next(-1, 1)));
            int s = max(10, min(10000, baseS + rnd.next(-3, 3) * 10));
            jobs.push_back({r, s});
        }
    } else if (mode == 2) {
        int n = rnd.next(6, 18);
        for (int i = 0; i < n; ++i) {
            int r = (i % 2 == 0) ? rnd.next(1, 4) : rnd.next(20, 100);
            int s = (i % 2 == 0) ? rnd.next(500, 1000) * 10 : rnd.next(1, 80) * 10;
            jobs.push_back({r, s});
        }
    } else if (mode == 3) {
        int n = rnd.next(8, 25);
        for (int i = 0; i < n; ++i) {
            int r = rnd.next(1, 100);
            int s = rnd.next(1, 1000) * 10;
            if (rnd.next(0, 4) == 0) r = rnd.any(vector<int>{1, 100});
            if (rnd.next(0, 4) == 0) s = rnd.any(vector<int>{10, 10000});
            jobs.push_back({r, s});
        }
    } else if (mode == 4) {
        int n = rnd.next(30, 100);
        for (int i = 0; i < n; ++i) {
            jobs.push_back({rnd.next(80, 100), randomStress()});
        }
    } else {
        int n = 100;
        for (int i = 0; i < n; ++i) {
            int r = (rnd.next(0, 3) == 0) ? 100 : rnd.next(1, 100);
            int s = (rnd.next(0, 3) == 0) ? 10000 : randomStress();
            jobs.push_back({r, s});
        }
    }

    shuffle(jobs.begin(), jobs.end());
    printJobs(jobs);

    return 0;
}
