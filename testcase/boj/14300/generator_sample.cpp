#include "testlib.h"
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    vector<pair<int, int>> cases;

    if (mode == 0) {
        int t = rnd.next(1, 12);
        for (int i = 0; i < t; ++i) {
            cases.push_back({rnd.next(1, 5), rnd.next(1, 5)});
        }
    } else if (mode == 1) {
        int t = rnd.next(8, 25);
        for (int i = 0; i < t; ++i) {
            int fixed = rnd.any(vector<int>{1, 2, 5});
            int other = rnd.next(1, 5);
            if (rnd.next(0, 1) == 0) {
                cases.push_back({fixed, other});
            } else {
                cases.push_back({other, fixed});
            }
        }
    } else if (mode == 2) {
        for (int r = 1; r <= 5; ++r) {
            for (int c = 1; c <= 5; ++c) {
                cases.push_back({r, c});
            }
        }
        shuffle(cases.begin(), cases.end());
    } else if (mode == 3) {
        int t = rnd.next(20, 60);
        for (int i = 0; i < t; ++i) {
            int r = rnd.next(3, 5);
            int c = rnd.next(3, 5);
            if (rnd.next(0, 3) == 0) {
                r = 5;
                c = 5;
            }
            cases.push_back({r, c});
        }
    } else {
        int t = 100;
        for (int i = 0; i < t; ++i) {
            cases.push_back({rnd.next(1, 5), rnd.next(1, 5)});
        }
    }

    println((int)cases.size());
    for (const auto& [r, c] : cases) {
        println(r, c);
    }

    return 0;
}
