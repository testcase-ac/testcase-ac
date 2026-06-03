#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int wrapHour(int hour) {
    while (hour < 1) hour += 12;
    while (hour > 12) hour -= 12;
    return hour;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<string, int>> cards;
    int n;

    int mode = rnd.next(0, 4);
    if (mode == 0) {
        n = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(9, 18);
    } else if (mode == 2) {
        n = rnd.next(12, 30);
    } else if (mode == 3) {
        n = rnd.next(20, 50);
    } else {
        n = rnd.next(60, 120);
    }

    int current = 0;
    int direction = 1;
    const vector<string> nonHourglass = {"CLOCK", "WATCH"};

    for (int i = 0; i < n; ++i) {
        current = wrapHour(current + direction);

        string kind;
        int x;
        int pattern = rnd.next(0, 99);

        if (pattern < 24) {
            kind = rnd.any(nonHourglass);
            x = current;
        } else if (pattern < 46) {
            kind = "HOURGLASS";
            x = current;
        } else if (pattern < 72) {
            kind = "HOURGLASS";
            x = wrapHour(current + rnd.next(1, 11));
        } else if (pattern < 86) {
            kind = rnd.any(nonHourglass);
            x = wrapHour(current + rnd.any(vector<int>{1, 11}));
        } else {
            kind = rnd.any(vector<string>{"CLOCK", "WATCH", "HOURGLASS"});
            x = rnd.next(1, 12);
        }

        cards.push_back({kind, x});

        if (kind == "HOURGLASS" && x != current) {
            direction *= -1;
        }
    }

    println(n);
    for (const auto& card : cards) {
        println(card.first, card.second);
    }

    return 0;
}
