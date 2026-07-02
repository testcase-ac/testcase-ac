#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

struct CaseData {
    int n;
    int b;
    vector<pair<int, int>> sticks;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 8);
    vector<CaseData> cases;

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int b = rnd.next(6, 80);
        int n = rnd.next(1, 12);
        vector<pair<int, int>> sticks;

        if (mode == 0) {
            int singleTypes = rnd.next(1, 4);
            int weakTypes = rnd.next(1, 3);
            for (int i = 0; i < singleTypes; ++i) {
                sticks.push_back({rnd.next(b, b + 40), rnd.next(1, 8)});
            }
            for (int i = 0; i < weakTypes; ++i) {
                sticks.push_back({rnd.next(1, b - 1), rnd.next(1, 10)});
            }
        } else if (mode == 1) {
            int low = rnd.next(1, b - 1);
            int high = rnd.next(max(1, b - low), b - 1);
            sticks.push_back({low, rnd.next(1, 8)});
            sticks.push_back({high, rnd.next(1, 8)});
            sticks.push_back({rnd.next(1, max(1, b / 2)), rnd.next(1, 6)});
            n = rnd.next(1, 8);
        } else if (mode == 2) {
            int p = rnd.next((b + 1) / 2, b - 1);
            sticks.push_back({p, rnd.next(1, 15)});
            sticks.push_back({rnd.next(1, max(1, b / 2)), rnd.next(1, 5)});
            n = rnd.next(1, 10);
        } else if (mode == 3) {
            int weakMax = max(1, b / 2 - 1);
            int m = rnd.next(2, 6);
            for (int i = 0; i < m; ++i) {
                sticks.push_back({rnd.next(1, weakMax), rnd.next(1, 5)});
            }
            n = rnd.next(4, 12);
        } else if (mode == 4) {
            int m = rnd.next(3, 8);
            for (int i = 0; i < m; ++i) {
                int p = rnd.next(1, b + 30);
                int q = rnd.next(1, 12);
                sticks.push_back({p, q});
            }
            sticks.push_back({b, rnd.next(1, 3)});
        } else {
            b = rnd.next(9000, 10000);
            n = rnd.next(1, 20);
            sticks.push_back({rnd.next(1, b - 1), rnd.next(1, 200000)});
            sticks.push_back({rnd.next(b, 20000), rnd.next(1, 200000)});
            sticks.push_back({rnd.next((b + 1) / 2, b - 1), rnd.next(1, 200000)});
        }

        while ((int)sticks.size() < rnd.next(2, 10)) {
            sticks.push_back({rnd.next(1, min(20000, b + 100)), rnd.next(1, 20)});
        }

        shuffle(sticks.begin(), sticks.end());
        cases.push_back({n, b, sticks});
    }

    println((int)cases.size());
    for (const CaseData& c : cases) {
        println(c.n, (int)c.sticks.size(), c.b);
        for (auto [p, q] : c.sticks) {
            println(p, q);
        }
    }

    return 0;
}
