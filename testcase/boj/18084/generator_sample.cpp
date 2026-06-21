#include "testlib.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string formatTime(int cents) {
    ostringstream out;
    out << cents / 100 << '.' << setw(2) << setfill('0') << cents % 100;
    return out.str();
}

int randomTime() {
    return rnd.next(100, 2000);
}

int clampTime(int cents) {
    return max(100, min(2000, cents));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> times(4);
    for (int& time : times) {
        time = randomTime();
    }

    vector<int> sorted = times;
    sort(sorted.begin(), sorted.end());

    int minMiddleSum = sorted[0] + sorted[1] + sorted[2];
    int maxMiddleSum = sorted[1] + sorted[2] + sorted[3];
    int mode = rnd.next(0, 5);
    int targetSum;

    if (mode == 0 && minMiddleSum > 300) {
        targetSum = rnd.next(300, min(6000, minMiddleSum - 1));
    } else if (mode == 1) {
        targetSum = rnd.next(max(300, maxMiddleSum), 6000);
    } else if (mode == 2) {
        targetSum = minMiddleSum;
    } else if (mode == 3) {
        targetSum = maxMiddleSum - rnd.next(1, max(1, maxMiddleSum - minMiddleSum));
    } else if (mode == 4) {
        int lastSolve = randomTime();
        targetSum = sorted[1] + sorted[2] + lastSolve;
    } else {
        targetSum = rnd.next(300, 6000);
    }

    int target = clampTime((targetSum + rnd.next(0, 2)) / 3);

    println(formatTime(times[0]), formatTime(times[1]), formatTime(times[2]), formatTime(times[3]));
    println(formatTime(target));

    return 0;
}
