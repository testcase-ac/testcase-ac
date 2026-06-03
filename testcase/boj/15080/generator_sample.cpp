#include "testlib.h"
#include <algorithm>
#include <array>

using namespace std;

struct Time {
    int hour;
    int minute;
    int second;
};

Time fromSeconds(int total) {
    total %= 24 * 60 * 60;
    if (total < 0) total += 24 * 60 * 60;
    return {total / 3600, (total / 60) % 60, total % 60};
}

void printTime(Time t) {
    println(t.hour, ":", t.minute, ":", t.second);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int day = 24 * 60 * 60;
    int mode = rnd.next(0, 5);
    Time start;
    Time end;

    if (mode == 0) {
        int hour = rnd.next(0, 23);
        int startSecond = rnd.next(0, 59 * 60 + 58);
        int duration = rnd.next(1, 59 * 60 + 59 - startSecond);
        start = {hour, startSecond / 60, startSecond % 60};
        end = {hour, (startSecond + duration) / 60, (startSecond + duration) % 60};
    } else if (mode == 1) {
        int base = rnd.next(0, day - 2);
        int duration = rnd.next(1, min(6 * 3600, day - 1 - base));
        start = fromSeconds(base);
        end = fromSeconds(base + duration);
    } else if (mode == 2) {
        int startSecond = rnd.next(20 * 3600, day - 1);
        int duration = rnd.next(1, min(8 * 3600, day - 1));
        start = fromSeconds(startSecond);
        end = fromSeconds(startSecond + duration);
    } else if (mode == 3) {
        array<int, 5> anchors = {0, 1, 59, 60, day - 1};
        int first = rnd.any(anchors);
        int delta = rnd.next(-120, 120);
        int second = first + delta;
        start = fromSeconds(first);
        end = fromSeconds(second);
    } else if (mode == 4) {
        int instant = rnd.next(0, day - 1);
        start = fromSeconds(instant);
        end = start;
    } else {
        start = fromSeconds(rnd.next(0, day - 1));
        end = fromSeconds(rnd.next(0, day - 1));
    }

    printTime(start);
    printTime(end);
    return 0;
}
