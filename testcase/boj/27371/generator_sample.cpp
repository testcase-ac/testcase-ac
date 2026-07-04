#include "testlib.h"
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> cases;

    int mode = rnd.next(0, 5);
    int t = rnd.next(1, 10);

    if (mode == 0) {
        for (int i = 0; i < t; ++i) {
            int n = rnd.next(1, 8);
            int m = rnd.next(n + 1, min(20, n + 12));
            cases.emplace_back(n, m);
        }
    } else if (mode == 1) {
        for (int i = 0; i < t; ++i) {
            int n = rnd.next(1, 99999);
            cases.emplace_back(n, n + 1);
        }
    } else if (mode == 2) {
        for (int i = 0; i < t; ++i) {
            int m = rnd.next(2, 100000);
            int n = rnd.next(1, m - 1);
            cases.emplace_back(n, m);
        }
    } else if (mode == 3) {
        for (int i = 0; i < t; ++i) {
            int n = rnd.next(1, 1000);
            int m = rnd.next(90000, 100000);
            if (n >= m) n = m - 1;
            cases.emplace_back(n, m);
        }
    } else if (mode == 4) {
        cases.emplace_back(1, 2);
        cases.emplace_back(1, 100000);
        cases.emplace_back(99999, 100000);
        while ((int)cases.size() < t) {
            int n = rnd.next(1, 99999);
            int gap = rnd.next(1, min(100000 - n, 50));
            cases.emplace_back(n, n + gap);
        }
    } else {
        for (int i = 0; i < t; ++i) {
            int bucket = rnd.next(0, 3);
            int n;
            if (bucket == 0) {
                n = rnd.next(1, 20);
            } else if (bucket == 1) {
                n = rnd.next(100, 5000);
            } else {
                n = rnd.next(50000, 99999);
            }
            int maxGap = min(100000 - n, max(1, n));
            int gap = rnd.next(1, maxGap);
            cases.emplace_back(n, n + gap);
        }
    }

    shuffle(cases.begin(), cases.end());
    if ((int)cases.size() > 10) cases.resize(10);

    println((int)cases.size());
    for (auto [n, m] : cases) {
        println(n, m);
    }

    return 0;
}
