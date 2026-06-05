#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <tuple>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(20, 60);
    vector<tuple<int, int, int>> cases;

    cases.emplace_back(1, 1, 1);
    cases.emplace_back(20, 10, 100);

    while ((int)cases.size() < t) {
        int mode = rnd.next(0, 5);
        int months, days, week;

        if (mode == 0) {
            months = rnd.next(1, 4);
            days = rnd.next(1, 3);
            week = rnd.next(1, 6);
        } else if (mode == 1) {
            days = rnd.next(1, 10);
            int multiplier = rnd.next(1, 10);
            week = min(100, days * multiplier);
            months = rnd.next(1, 20);
        } else if (mode == 2) {
            week = rnd.next(1, 100);
            days = rnd.next(1, 10);
            months = rnd.next(15, 20);
        } else if (mode == 3) {
            days = rnd.next(6, 10);
            week = rnd.next(1, 10);
            months = rnd.next(1, 20);
        } else if (mode == 4) {
            week = rnd.next(11, 100);
            days = rnd.next(1, 10);
            months = rnd.next(1, 20);
        } else {
            days = rnd.next(1, 10);
            week = rnd.next(1, 100);
            int period = week / gcd(days, week);
            months = rnd.next(1, min(20, max(1, period * rnd.next(1, 4))));
        }

        cases.emplace_back(months, days, week);
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (const auto& [months, days, week] : cases) {
        println(months, days, week);
    }

    return 0;
}
