#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

pair<int, int> randomCase(int nLo, int nHi) {
    int n = rnd.next(nLo, nHi);
    int mode = rnd.next(0, 5);
    int k;

    if (mode == 0) {
        k = 1;
    } else if (mode == 1) {
        k = n;
    } else if (mode == 2) {
        k = rnd.next(1, min(n, 3));
    } else if (mode == 3) {
        k = rnd.next(max(1, n - 2), n);
    } else if (mode == 4) {
        k = (n + 1) / 2;
    } else {
        k = rnd.next(1, n);
    }

    return {n, k};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<pair<int, int>> cases;

    if (mode == 0) {
        int t = rnd.next(1, 8);
        for (int i = 0; i < t; ++i) {
            cases.push_back(randomCase(1, 8));
        }
    } else if (mode == 1) {
        int t = rnd.next(8, 25);
        for (int i = 0; i < t; ++i) {
            cases.push_back(randomCase(1, 40));
        }
    } else if (mode == 2) {
        int t = rnd.next(4, 12);
        for (int i = 0; i < t; ++i) {
            cases.push_back(randomCase(50, 250));
        }
    } else if (mode == 3) {
        int t = rnd.next(3, 8);
        for (int i = 0; i < t; ++i) {
            cases.push_back(randomCase(1000, 5000));
        }
    } else if (mode == 4) {
        cases = {{1, 1}, {2, 1}, {2, 2}, {3, 2}, {5000, 1}, {5000, 5000}};
        int extra = rnd.next(1, 6);
        for (int i = 0; i < extra; ++i) {
            cases.push_back(randomCase(4900, 5000));
        }
        shuffle(cases.begin(), cases.end());
    } else {
        int n = rnd.next(1, 5000);
        for (int k : {1, max(1, n / 2), n}) {
            cases.push_back({n, k});
        }
        int extra = rnd.next(0, 5);
        for (int i = 0; i < extra; ++i) {
            cases.push_back(randomCase(max(1, n - 10), min(5000, n + 10)));
        }
    }

    println((int)cases.size());
    for (auto [n, k] : cases) {
        println(n, k);
    }

    return 0;
}
