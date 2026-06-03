#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

const int MAX_N = 1000000;

bool isPrime(int x) {
    if (x < 2) return false;
    for (int d = 2; d * d <= x; ++d)
        if (x % d == 0) return false;
    return true;
}

int clampN(int n) {
    return max(1, min(MAX_N, n));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<int> queries;

    if (mode == 0) {
        int t = rnd.next(1, 20);
        int hi = rnd.next(1, 30);
        for (int i = 0; i < t; ++i) queries.push_back(rnd.next(1, hi));
    } else if (mode == 1) {
        vector<int> base = {1, 2, 3, 4, 5, 8, 10, 100, 1000, 10000, MAX_N};
        shuffle(base.begin(), base.end());
        int t = rnd.next(1, (int)base.size());
        queries.assign(base.begin(), base.begin() + t);
    } else if (mode == 2) {
        int t = rnd.next(5, 35);
        int center = rnd.next(1, MAX_N);
        int radius = rnd.next(0, 50);
        for (int i = 0; i < t; ++i) queries.push_back(clampN(center + rnd.next(-radius, radius)));
    } else if (mode == 3) {
        int t = rnd.next(5, 40);
        int start = rnd.next(1, MAX_N);
        int step = rnd.next(1, 1000);
        for (int i = 0; i < t; ++i) queries.push_back(clampN(start + i * step));
        shuffle(queries.begin(), queries.end());
    } else if (mode == 4) {
        int t = rnd.next(5, 30);
        for (int i = 0; i < t; ++i) {
            int n = rnd.next(1, MAX_N);
            if (rnd.next(0, 1)) n = MAX_N - rnd.next(0, 1000);
            queries.push_back(clampN(n));
        }
    } else {
        int t = rnd.next(5, 30);
        while ((int)queries.size() < t) {
            int n = rnd.next(1, MAX_N);
            for (int delta = -2; delta <= 2 && (int)queries.size() < t; ++delta) {
                int candidate = clampN(n + delta);
                if (isPrime(3 * candidate + 7) || rnd.next(0, 3) == 0) {
                    queries.push_back(candidate);
                }
            }
        }
    }

    println((int)queries.size());
    for (int n : queries) println(n);

    return 0;
}
