#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int a = 0;
    int b = 0;
    int c = 0;
    vector<pair<int, int>> trips;

    if (mode == 0) {
        a = rnd.next(3, 12);
        b = rnd.next(1, a);
        c = rnd.next(1, b);
        int day = 1;
        while (day <= a) {
            if (rnd.next(0, 1) == 0) {
                ++day;
                continue;
            }
            int len = rnd.next(1, min(3, a - day + 1));
            trips.push_back({day, day + len - 1});
            day += len + rnd.next(0, 2);
        }
    } else if (mode == 1) {
        a = rnd.next(20, 80);
        b = rnd.next(5, min(25, a));
        c = rnd.next(1, b);
        int len = rnd.next(max(1, c), min(a, b + 3));
        int start = rnd.next(1, a - len + 1);
        trips.push_back({start, start + len - 1});
    } else if (mode == 2) {
        a = rnd.next(30, 120);
        b = rnd.next(2, min(30, a));
        c = rnd.next(1, b);
        int n = rnd.next(2, 8);
        int day = rnd.next(1, 4);
        for (int i = 0; i < n && day <= a; ++i) {
            int len = rnd.next(1, min(5, a - day + 1));
            trips.push_back({day, day + len - 1});
            day += len + rnd.next(1, 10);
        }
    } else if (mode == 3) {
        a = rnd.next(1, 20);
        b = a;
        c = rnd.next(1, b);
        int day = 1;
        while (day <= a) {
            int len = rnd.next(1, min(2, a - day + 1));
            trips.push_back({day, day + len - 1});
            day += len + rnd.next(1, 2);
        }
    } else {
        a = rnd.next(50, 200);
        b = rnd.next(max(1, a - 20), a);
        c = rnd.next(1, b);
        int leftLen = rnd.next(1, min(8, a));
        trips.push_back({1, leftLen});
        int rightLen = rnd.next(1, min(8, a - leftLen));
        trips.push_back({a - rightLen + 1, a});
        if (leftLen + 2 < a - rightLen + 1 && rnd.next(0, 1)) {
            int midStart = rnd.next(leftLen + 2, a - rightLen);
            int midLen = rnd.next(1, min(5, a - rightLen - midStart + 1));
            trips.push_back({midStart, midStart + midLen - 1});
        }
    }

    if (trips.empty()) {
        trips.push_back({1, 1});
    }

    sort(trips.begin(), trips.end());
    vector<pair<int, int>> merged;
    for (auto trip : trips) {
        if (!merged.empty() && merged.back().second >= trip.first) {
            continue;
        }
        merged.push_back(trip);
    }
    trips = merged;
    shuffle(trips.begin(), trips.end());

    println((int)trips.size(), a, b, c);
    for (auto trip : trips) {
        println(trip.first, trip.second);
    }

    return 0;
}
