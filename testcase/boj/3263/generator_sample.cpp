#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = (mode == 5) ? rnd.next(100, 300) : rnd.next(1, 30);
    int k = rnd.next(1, (mode == 5) ? 120 : 35);

    vector<pair<int, int>> jobs;

    auto addJob = [&](int p, int t) {
        p = max(1, min(p, n));
        t = max(1, min(t, n - p + 1));
        jobs.push_back({p, t});
    };

    if (mode == 0) {
        int p = rnd.next(1, n);
        for (int i = 0; i < k; ++i) {
            addJob(p, rnd.next(1, n - p + 1));
        }
    } else if (mode == 1) {
        int clusterCount = rnd.next(1, min(5, n));
        vector<int> starts;
        for (int i = 0; i < clusterCount; ++i) starts.push_back(rnd.next(1, n));
        for (int i = 0; i < k; ++i) {
            int p = rnd.any(starts);
            addJob(p, rnd.next(1, n - p + 1));
        }
    } else if (mode == 2) {
        for (int i = 0; i < k; ++i) {
            int p = rnd.next(1, n);
            int maxT = n - p + 1;
            int t = (rnd.next(0, 2) == 0) ? 1 : rnd.next(max(1, maxT / 2), maxT);
            addJob(p, t);
        }
    } else if (mode == 3) {
        int p = 1;
        while ((int)jobs.size() < k && p <= n) {
            int t = rnd.next(1, n - p + 1);
            addJob(p, t);
            p += rnd.next(1, 4);
        }
        while ((int)jobs.size() < k) {
            p = rnd.next(1, n);
            addJob(p, rnd.next(1, n - p + 1));
        }
    } else if (mode == 4) {
        addJob(1, n);
        if (n > 1) addJob(n, 1);
        while ((int)jobs.size() < k) {
            int p = rnd.next(1, n);
            int t = rnd.next(1, n - p + 1);
            addJob(p, t);
        }
    } else {
        for (int i = 0; i < k; ++i) {
            int p = rnd.wnext(n, -2) + 1;
            int maxT = n - p + 1;
            int t = rnd.wnext(maxT, 2) + 1;
            addJob(p, t);
        }
    }

    shuffle(jobs.begin(), jobs.end());

    println(n, (int)jobs.size());
    for (auto job : jobs) {
        println(job.first, job.second);
    }

    return 0;
}
