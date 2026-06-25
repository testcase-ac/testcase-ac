#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int datasets = rnd.next(1, 20);
    vector<pair<int, int>> cases;
    cases.reserve(datasets);

    for (int i = 0; i < datasets; ++i) {
        int mode = rnd.next(100);
        int m, n;

        if (mode < 20) {
            vector<pair<int, int>> edges = {
                {2, 1},
                {2, 500000},
                {100, 1},
                {100, 500000},
            };
            auto edge = rnd.any(edges);
            m = edge.first;
            n = edge.second;
        } else if (mode < 45) {
            m = rnd.next(2, 10);
            n = rnd.next(1, 30);
        } else if (mode < 70) {
            m = rnd.next(11, 60);
            n = rnd.next(1, 1000);
        } else if (mode < 88) {
            m = rnd.next(61, 100);
            n = rnd.next(1, 500000);
        } else {
            m = rnd.next(2, 5);
            n = rnd.next(400000, 500000);
        }

        cases.push_back({m, n});
    }

    shuffle(cases.begin(), cases.end());
    for (auto [m, n] : cases) {
        println(m, n);
    }
    println(0, 0);

    return 0;
}
