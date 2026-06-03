#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int queryCount = rnd.next(1, 20);
    if (mode == 0) {
        queryCount = rnd.next(1, 5);
    } else if (mode == 1) {
        queryCount = rnd.next(8, 20);
    }

    vector<int> landmarks = {1, 2, 3, 4, 6, 8, 9, 10, 11, 20, 50, 100, 250, 489, 490};
    vector<int> hours;

    for (int i = 0; i < queryCount; ++i) {
        int hour;
        if (mode == 0) {
            hour = rnd.any(landmarks);
        } else if (mode == 1) {
            hour = rnd.next(1, 20);
        } else if (mode == 2) {
            hour = rnd.next(450, 490);
        } else if (mode == 3) {
            hour = (i % 2 == 0) ? rnd.next(1, 15) : rnd.next(475, 490);
        } else if (mode == 4) {
            hour = rnd.next(1, 490);
        } else {
            hour = rnd.any(landmarks);
            if (rnd.next(0, 2) == 0) {
                hour = rnd.next(1, 490);
            }
        }
        hours.push_back(hour);
    }

    if (rnd.next(0, 3) == 0) {
        shuffle(hours.begin(), hours.end());
    }

    for (int hour : hours) {
        println(hour);
    }
    println(-1);

    return 0;
}
