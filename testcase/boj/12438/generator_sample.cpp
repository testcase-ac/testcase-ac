#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(20, 40);
    vector<tuple<long long, int, int>> cases;

    cases.emplace_back(1, 1, 1);
    cases.emplace_back(3, 11, 4);
    cases.emplace_back(12, 28, 7);
    cases.emplace_back(10, 35, 10);
    cases.emplace_back(1000000000000LL, 1000000, 100);

    while ((int)cases.size() < t) {
        int mode = rnd.next(0, 7);
        long long months;
        int daysPerMonth;
        int daysPerWeek;

        if (mode == 0) {
            months = rnd.next(1, 12);
            daysPerMonth = rnd.next(1, 31);
            daysPerWeek = rnd.next(1, 10);
        } else if (mode == 1) {
            daysPerWeek = rnd.next(1, 20);
            daysPerMonth = daysPerWeek * rnd.next(1, max(1, 100 / daysPerWeek));
            months = rnd.next(1, 80);
        } else if (mode == 2) {
            daysPerWeek = rnd.next(2, 100);
            daysPerMonth = rnd.next(1, min(1000000, daysPerWeek * rnd.next(1, 10000)));
            months = rnd.next(1LL, 100000LL);
        } else if (mode == 3) {
            daysPerWeek = rnd.next(90, 100);
            daysPerMonth = rnd.next(999000, 1000000);
            months = rnd.next(999999000000LL, 1000000000000LL);
        } else if (mode == 4) {
            daysPerWeek = rnd.any(vector<int>{1, 2, 4, 5, 10, 20, 25, 50, 100});
            daysPerMonth = rnd.next(1, 1000000);
            months = rnd.next(1LL, 1000000000000LL);
        } else if (mode == 5) {
            daysPerWeek = rnd.next(1, 100);
            daysPerMonth = rnd.next(1, 1000000);
            long long period = daysPerWeek / __gcd(daysPerMonth, daysPerWeek);
            months = period * rnd.next(1LL, max(1LL, 1000000000000LL / period));
        } else if (mode == 6) {
            daysPerWeek = rnd.next(1, 100);
            daysPerMonth = rnd.next(1, 1000000);
            months = rnd.next(999999999900LL, 1000000000000LL);
        } else {
            daysPerWeek = rnd.next(1, 100);
            daysPerMonth = rnd.next(1, 1000000);
            months = rnd.next(1LL, 1000000000000LL);
        }

        cases.emplace_back(months, daysPerMonth, daysPerWeek);
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (const auto& [months, daysPerMonth, daysPerWeek] : cases) {
        println(months, daysPerMonth, daysPerWeek);
    }

    return 0;
}
