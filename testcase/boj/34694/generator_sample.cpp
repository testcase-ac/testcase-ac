#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long randomFloor(int profile) {
    if (profile == 0) return rnd.next(1, 20);
    if (profile == 1) return rnd.next(1, 200);
    if (profile == 2) return rnd.next(999999900, 1000000000);
    if (rnd.next(0, 4) == 0) return 1;
    if (rnd.next(0, 3) == 0) return rnd.next(999999950, 1000000000);
    return rnd.next(1, 1000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int w = rnd.next(1, 12);
    int m = rnd.next(2, 10);
    int b = rnd.next(1, m - 1);

    if (mode == 0) {
        w = 1;
        m = rnd.next(2, 8);
        b = rnd.next(1, m - 1);
    } else if (mode == 1) {
        m = 2;
        b = 1;
    } else if (mode == 2) {
        w = rnd.next(8, 20);
        m = rnd.next(2, 6);
        b = rnd.next(1, m - 1);
    } else if (mode == 3) {
        m = rnd.next(6, 14);
        b = rnd.next(1, m - 1);
    }

    int capacityForFlexible = (m - b) * w;
    int a;
    if (mode == 1) {
        a = capacityForFlexible;
    } else if (mode == 4) {
        a = rnd.next(max(1, capacityForFlexible / 2), capacityForFlexible);
    } else {
        a = rnd.next(1, capacityForFlexible);
    }

    int profile = rnd.next(0, 3);
    vector<long long> flexible(a);
    for (long long& floor : flexible) {
        floor = randomFloor(profile);
    }

    vector<vector<long long>> fixed(w, vector<long long>(b));
    for (int day = 0; day < w; ++day) {
        int dayProfile = (mode == 5 ? day % 4 : profile);
        for (int i = 0; i < b; ++i) {
            fixed[day][i] = randomFloor(dayProfile);
        }
        if (mode == 3 && day % 3 == 0) {
            fixed[day][rnd.next(0, b - 1)] = 1000000000LL;
        }
    }

    if (rnd.next(0, 1)) {
        sort(flexible.begin(), flexible.end());
    } else {
        shuffle(flexible.begin(), flexible.end());
    }

    println(a, b, w, m);
    for (long long floor : flexible) {
        println(floor);
    }
    for (const vector<long long>& day : fixed) {
        println(day);
    }

    return 0;
}
