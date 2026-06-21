#include "testlib.h"

#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> cases;

    int mode = rnd.next(0, 5);
    if (mode == 0) {
        cases.emplace_back(3500, rnd.next(1, 8000));
    } else if (mode == 1) {
        cases.emplace_back(5000, rnd.next(1, 8000));
    } else if (mode == 2) {
        cases.emplace_back(rnd.next(3500, 5000), 1);
    } else if (mode == 3) {
        cases.emplace_back(rnd.next(3500, 5000), 8000);
    } else if (mode == 4) {
        int count = rnd.next(2, 8);
        for (int i = 0; i < count; ++i) {
            int n = rnd.next(3500, 5000);
            int t = rnd.next(1, 8000);
            cases.emplace_back(n, t);
        }
    } else {
        cases.emplace_back(3500, 1);
        cases.emplace_back(5000, 8000);
        cases.emplace_back(rnd.next(3500, 5000), rnd.next(1, 8000));
    }

    for (auto [n, t] : cases) {
        println(n, t);
    }
    println(0, 0);

    return 0;
}
