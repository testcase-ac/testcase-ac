#include "testlib.h"
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> cases;

    int mode = rnd.next(0, 5);
    if (mode == 0) {
        int x = rnd.next(1, 10);
        cases.push_back({x, x});
    } else if (mode == 1) {
        int x = rnd.next(1, 10);
        cases.push_back({x, 1});
    } else if (mode == 2) {
        int x = rnd.next(1, 10);
        cases.push_back({1, x});
    } else if (mode == 3) {
        vector<pair<int, int>> reduced;
        for (int a = 1; a <= 10; ++a) {
            for (int b = 1; b <= 10; ++b) {
                if (gcd(a, b) == 1) reduced.push_back({a, b});
            }
        }
        cases.push_back(rnd.any(reduced));
    } else if (mode == 4) {
        cases.push_back({rnd.next(7, 10), rnd.next(1, 4)});
    } else {
        cases.push_back({rnd.next(1, 10), rnd.next(1, 10)});
    }

    auto [a, b] = rnd.any(cases);
    println(a, b);
    return 0;
}
