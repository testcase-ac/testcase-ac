#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<int> days;

    if (mode == 0) {
        int n = rnd.next(1, 4);
        int day = rnd.next(1, 5);
        days.assign(n, day);
    } else if (mode == 1) {
        int missing = rnd.next(1, 5);
        int n = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) {
            int day = rnd.next(1, 4);
            if (day >= missing) ++day;
            days.push_back(day);
        }
    } else if (mode == 2) {
        days = {1, 2, 3, 4, 5};
        int extra = rnd.next(0, 8);
        for (int i = 0; i < extra; ++i) {
            days.push_back(rnd.next(1, 5));
        }
    } else if (mode == 3) {
        int n = rnd.next(20, 50);
        for (int i = 0; i < n; ++i) {
            days.push_back(rnd.next(1, 5));
        }
    } else if (mode == 4) {
        int used = rnd.next(1, 4);
        vector<int> pool = {1, 2, 3, 4, 5};
        shuffle(pool.begin(), pool.end());
        pool.resize(used);

        int n = rnd.next(used, 50);
        for (int i = 0; i < used; ++i) {
            days.push_back(pool[i]);
        }
        for (int i = used; i < n; ++i) {
            days.push_back(rnd.any(pool));
        }
    } else {
        int n = rnd.next(5, 50);
        days = {1, 2, 3, 4, 5};
        for (int i = 5; i < n; ++i) {
            days.push_back(rnd.next(1, 5));
        }
    }

    shuffle(days.begin(), days.end());

    println(static_cast<int>(days.size()));
    for (int day : days) {
        println(day);
    }

    return 0;
}
