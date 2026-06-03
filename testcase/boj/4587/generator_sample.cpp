#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int targetCases = rnd.next(1, 30);
    set<pair<int, int>> used;
    vector<pair<int, int>> cases;

    auto addCase = [&](int m, int n) {
        if (1 < m && m < n && n < 100 && gcd(m, n) == 1 && used.insert({m, n}).second) {
            cases.push_back({m, n});
        }
    };

    int attempts = 0;
    while ((int)cases.size() < targetCases && attempts++ < 2000) {
        int mode = rnd.next(0, 5);
        int m = 0;
        int n = 0;

        if (mode == 0) {
            n = rnd.next(3, 20);
            m = rnd.next(2, n - 1);
        } else if (mode == 1) {
            n = rnd.next(50, 99);
            m = rnd.next(max(2, n - 8), n - 1);
        } else if (mode == 2) {
            m = 2;
            n = rnd.next(3, 99);
        } else if (mode == 3) {
            n = rnd.next(80, 99);
            m = rnd.next(2, min(20, n - 1));
        } else if (mode == 4) {
            n = rnd.next(10, 99);
            m = rnd.next(2, n - 1);
        } else {
            vector<pair<int, int>> edges = {
                {3, 4}, {2, 7}, {9, 20}, {17, 69}, {97, 98}, {3, 97}, {49, 98},
            };
            auto chosen = rnd.any(edges);
            m = chosen.first;
            n = chosen.second;
        }

        addCase(m, n);
    }

    if (cases.empty()) {
        addCase(2, 3);
    }

    shuffle(cases.begin(), cases.end());
    for (auto [m, n] : cases) {
        println(m, n);
    }
    println(0, 0);

    return 0;
}
