#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> cases;

    int mode = rnd.next(0, 4);
    if (mode == 0) {
        int t = rnd.next(8, 18);
        for (int i = 0; i < t; ++i) {
            int c = rnd.next(1, 10);
            int n = rnd.next(1, c);
            cases.push_back({c, n});
        }
    } else if (mode == 1) {
        int t = rnd.next(6, 14);
        for (int i = 0; i < t; ++i) {
            int c = rnd.next(1, 10);
            int n = rnd.next(0, 1) == 0 ? 1 : c;
            cases.push_back({c, n});
        }
    } else if (mode == 2) {
        int t = rnd.next(8, 20);
        for (int i = 0; i < t; ++i) {
            int c = rnd.next(2, 10);
            int lo = max(1, c / 2 - 1);
            int hi = min(c, c / 2 + 2);
            int n = rnd.next(lo, hi);
            cases.push_back({c, n});
        }
    } else if (mode == 3) {
        int t = rnd.next(20, 45);
        for (int i = 0; i < t; ++i) {
            int c = rnd.next(1, 10);
            int bias = rnd.next(0, 3);
            int n;
            if (bias == 0) {
                n = 1;
            } else if (bias == 1) {
                n = c;
            } else {
                n = rnd.next(1, c);
            }
            cases.push_back({c, n});
        }
    } else {
        int t = rnd.next(70, 100);
        for (int i = 0; i < t; ++i) {
            int c = rnd.next(1, 10);
            int n = rnd.wnext(c, rnd.next(-2, 2)) + 1;
            cases.push_back({c, n});
        }
    }

    cases.push_back({1, 1});
    cases.push_back({10, 1});
    cases.push_back({10, 10});
    cases.push_back({10, rnd.next(2, 9)});
    cases.push_back({rnd.next(2, 10), 1});

    shuffle(cases.begin(), cases.end());
    if (cases.size() > 100) {
        cases.resize(100);
    }

    println(static_cast<int>(cases.size()));
    for (const auto& [c, n] : cases) {
        println(c, n);
    }

    return 0;
}
