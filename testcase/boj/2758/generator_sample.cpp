#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> cases;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        println(0);
        return 0;
    }

    if (mode == 1) {
        cases.push_back({rnd.next(1, 10), 2000});
    } else if (mode == 2) {
        int n = rnd.next(1, 10);
        cases.push_back({n, n});
    } else {
        int t = rnd.next(1, 25);
        for (int i = 0; i < t; ++i) {
            int n = rnd.next(1, 10);
            int shape = rnd.next(0, 5);
            int m;

            if (shape == 0) {
                m = n;
            } else if (shape == 1) {
                m = rnd.next(n, min(25, max(n, n * 3)));
            } else if (shape == 2) {
                m = rnd.next(max(n, 900), 2000);
            } else if (shape == 3) {
                int p = rnd.next(0, 11);
                m = min(2000, max(n, 1 << p));
            } else {
                m = rnd.next(n, 2000);
            }

            cases.push_back({n, m});
        }
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (const auto& tc : cases) {
        println(tc.first, tc.second);
    }

    return 0;
}
