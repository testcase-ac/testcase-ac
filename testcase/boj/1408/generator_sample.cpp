#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

string twoDigits(int value) {
    return string(1, char('0' + value / 10)) + char('0' + value % 10);
}

string formatTime(int seconds) {
    int hour = seconds / 3600;
    int minute = (seconds / 60) % 60;
    int second = seconds % 60;

    return twoDigits(hour) + ":" + twoDigits(minute) + ":" + twoDigits(second);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int day = 24 * 60 * 60;
    int mode = rnd.next(0, 4);
    int current = 0;
    int offset = 1;

    if (mode == 0) {
        vector<int> anchors = {0, 1, 59, 60, 3599, 3600, 43199, 43200, 86398, 86399};
        current = rnd.any(anchors);
        offset = rnd.next(1, 120);
    } else if (mode == 1) {
        current = rnd.next(day - 180, day - 1);
        offset = rnd.next(1, 240);
    } else if (mode == 2) {
        current = rnd.next(0, day - 1);
        vector<int> offsets = {1, 59, 60, 61, 3599, 3600, 3601, 43200, 86399};
        offset = rnd.any(offsets);
    } else if (mode == 3) {
        current = rnd.next(0, day - 1);
        offset = rnd.next(1, 600);
    } else {
        current = rnd.next(0, day - 1);
        offset = rnd.next(1, day - 1);
    }

    int start = (current + offset) % day;
    println(formatTime(current));
    println(formatTime(start));

    return 0;
}
