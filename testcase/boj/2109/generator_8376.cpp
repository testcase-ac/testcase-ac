#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose number of lectures with variability, including edge case n=0
    int mode_n = rnd.next(0, 3);
    int n;
    switch (mode_n) {
        case 0: n = 0; break;
        case 1: n = rnd.next(1, 5); break;
        case 2: n = rnd.next(6, 15); break;
        default: n = rnd.next(10, 20); break;
    }
    vector<pair<int,int>> jobs;
    jobs.reserve(n);
    for (int i = 0; i < n; i++) {
        // Deadline mode: tight small, relative to n, or wide
        int dl_mode = rnd.next(0, 2);
        int d;
        if (dl_mode == 0) {
            d = rnd.next(1, 5);
        } else if (dl_mode == 1) {
            d = rnd.next(1, max(1, n));
        } else {
            d = rnd.next(1, 50);
        }
        // Payment mode: uniform small or skewed large
        int pay_mode = rnd.next(0, 1);
        int p;
        if (pay_mode == 0) {
            p = rnd.next(1, 100);
        } else {
            p = rnd.wnext(10000, 1) + 1;
        }
        jobs.emplace_back(p, d);
    }
    // Shuffle input order to avoid sorted patterns
    shuffle(jobs.begin(), jobs.end());
    // Output
    println(n);
    for (auto &job : jobs) {
        println(job.first, job.second);
    }
    return 0;
}
