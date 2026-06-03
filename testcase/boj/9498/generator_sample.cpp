#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> thresholds = {0, 1, 59, 60, 69, 70, 79, 80, 89, 90, 99, 100};
    int mode = rnd.next(0, 3);
    int score;

    if (mode == 0) {
        score = rnd.any(thresholds);
    } else if (mode == 1) {
        int base = rnd.any(vector<int>{60, 70, 80, 90});
        score = base + rnd.next(-1, 1);
    } else if (mode == 2) {
        int grade = rnd.next(0, 4);
        vector<pair<int, int>> ranges = {
            {90, 100},
            {80, 89},
            {70, 79},
            {60, 69},
            {0, 59},
        };
        score = rnd.next(ranges[grade].first, ranges[grade].second);
    } else {
        score = rnd.next(0, 100);
    }

    println(score);
    return 0;
}
