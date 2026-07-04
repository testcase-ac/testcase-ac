#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Day {
    int cups;
    int lemonPrice;
    int sugarPrice;
};

int boundedPrice(int value, int lo, int hi) {
    return max(lo, min(hi, value));
}

vector<Day> makeDays(int d, int mode, int sugarPerCup) {
    vector<Day> days;
    days.reserve(d);

    int lemonBase = rnd.next(4, 45);
    int sugarBase = rnd.next(40, 460);
    int lemonTrend = rnd.next(-4, 4);
    int sugarTrend = rnd.next(-45, 45);

    for (int i = 0; i < d; ++i) {
        int cups;
        if (mode == 0) {
            cups = rnd.next(1, 20);
        } else if (mode == 1) {
            cups = rnd.next(80, 220);
        } else if (mode == 2) {
            int targetSugar = 80 * rnd.next(1, 5) + rnd.next(-2, 2);
            cups = max(1, min(1000, (targetSugar + sugarPerCup - 1) / sugarPerCup));
        } else {
            cups = rnd.next(1, 1000);
        }

        int lemonPrice;
        int sugarPrice;
        if (mode == 0) {
            lemonPrice = boundedPrice(lemonBase + i * lemonTrend + rnd.next(-2, 2), 1, 50);
            sugarPrice = boundedPrice(sugarBase + i * sugarTrend + rnd.next(-20, 20), 1, 500);
        } else if (mode == 1) {
            lemonPrice = boundedPrice(lemonBase - i * rnd.next(0, 3) + rnd.next(-1, 1), 1, 50);
            sugarPrice = boundedPrice(sugarBase - i * rnd.next(0, 35) + rnd.next(-10, 10), 1, 500);
        } else if (mode == 2) {
            lemonPrice = (i % 2 == 0) ? rnd.next(1, 12) : rnd.next(35, 50);
            sugarPrice = (i % 3 == 0) ? rnd.next(1, 90) : rnd.next(250, 500);
        } else {
            lemonPrice = rnd.next(1, 50);
            sugarPrice = rnd.next(1, 500);
        }

        days.push_back({cups, lemonPrice, sugarPrice});
    }

    return days;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 8);
    println(n);

    for (int tc = 0; tc < n; ++tc) {
        int mode = rnd.next(0, 3);
        int d = (mode == 3) ? rnd.next(1, 12) : rnd.next(1, 8);
        int lemonsPerCup = rnd.next(1, 10);
        int sugarPerCup = rnd.next(1, 10);

        println(d, lemonsPerCup, sugarPerCup);
        vector<Day> days = makeDays(d, mode, sugarPerCup);
        for (const Day& day : days) {
            println(day.cups, day.lemonPrice, day.sugarPrice);
        }
    }

    return 0;
}
