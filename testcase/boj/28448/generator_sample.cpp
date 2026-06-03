#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, mode == 4 ? 80 : 24);
    long long l;

    if (mode == 0) {
        l = rnd.next(1, 40);
    } else if (mode == 1) {
        l = rnd.next(30, 300);
    } else if (mode == 2) {
        l = rnd.next(500, 20000);
    } else if (mode == 3) {
        l = 1LL * rnd.next(5000, 100000) * rnd.next(1000, 10000);
        l = min(l, 1000000000LL);
    } else {
        l = rnd.next(1, 1000000000);
    }

    vector<pair<int, int>> problems;
    problems.reserve(n);

    for (int i = 0; i < n; ++i) {
        int t;
        if (mode == 0) {
            t = rnd.next(1, (int)min(8LL, l));
        } else if (mode == 1) {
            t = rnd.next(1, (int)min(30LL, l));
        } else if (mode == 2) {
            t = rnd.next(1, 100);
        } else if (mode == 3) {
            t = rnd.next(6, 100000);
        } else {
            t = rnd.next(1, 100000);
        }

        t = min<long long>(t, l);
        int maxK = (int)min(100000LL, l / t);
        int k;

        if (maxK == 1) {
            k = 1;
        } else if (mode == 0 || mode == 3) {
            k = rnd.next(max(1, maxK - min(maxK - 1, 5)), maxK);
        } else if (mode == 1) {
            k = rnd.next(1, maxK);
        } else if (mode == 2) {
            int bucket = rnd.next(0, 2);
            if (bucket == 0) {
                t = rnd.next(1, 5);
            } else if (bucket == 1) {
                t = rnd.next(6, min(100000, max(6, (int)min(100000LL, l))));
            }
            t = min<long long>(t, l);
            maxK = (int)min(100000LL, l / t);
            k = rnd.next(1, maxK);
        } else {
            k = rnd.next(1, maxK);
        }

        problems.emplace_back(k, t);
    }

    if (mode == 3) {
        sort(problems.begin(), problems.end(), greater<pair<int, int>>());
    } else if (mode == 4) {
        shuffle(problems.begin(), problems.end());
    }

    println(n, l);
    for (const auto& problem : problems) {
        println(problem.first, problem.second);
    }

    return 0;
}
