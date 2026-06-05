#include "testlib.h"

#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

const int MIN_TIME = 5 * 3600;
const int MAX_TIME = 23 * 3600 + 59 * 60;

void printTime(int value) {
    int hour = value / 3600;
    int minute = value / 60 % 60;
    int second = value % 60;
    printf("%02d:%02d:%02d\n", hour, minute, second);
}

vector<int> denseSchedule(int count, int start, int gap) {
    vector<int> times;
    times.reserve(count);
    for (int i = 0; i < count; ++i) {
        times.push_back(start + i * gap);
    }
    return times;
}

vector<int> randomSchedule(int count, int lo, int hi) {
    vector<int> candidates;
    for (int t = lo; t <= hi; t += 60) {
        candidates.push_back(t);
    }
    shuffle(candidates.begin(), candidates.end());
    candidates.resize(count);
    sort(candidates.begin(), candidates.end());
    return candidates;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    vector<int> up;
    vector<int> down;

    if (mode == 0) {
        up = {MIN_TIME};
        down = {MAX_TIME};
    } else if (mode == 1) {
        int count = rnd.next(1, 8);
        int start = rnd.next(MIN_TIME, MIN_TIME + 2 * 3600);
        start -= start % 60;
        up = denseSchedule(count, start, 60);
        down = denseSchedule(count, start + rnd.next(0, 39), 60);
    } else if (mode == 2) {
        int upCount = rnd.next(2, 10);
        int downCount = rnd.next(2, 10);
        int start = rnd.next(MIN_TIME + 600, 20 * 3600);
        start -= start % 60;
        up = denseSchedule(upCount, start, 60);
        down = denseSchedule(downCount, start + rnd.next(20, 59), 60);
    } else if (mode == 3) {
        int upCount = rnd.next(1, 12);
        int downCount = rnd.next(1, 12);
        up = randomSchedule(upCount, MIN_TIME, MAX_TIME);
        down = randomSchedule(downCount, MIN_TIME, MAX_TIME);
    } else if (mode == 4) {
        int upCount = rnd.next(1, 6);
        int downCount = rnd.next(1, 6);
        up = denseSchedule(upCount, MAX_TIME - (upCount - 1) * 60, 60);
        down = denseSchedule(downCount, MAX_TIME - (downCount - 1) * 60, 60);
    } else {
        int upCount = rnd.next(30, 80);
        int downCount = rnd.next(30, 80);
        int latestStart = MAX_TIME - 59 - 79 * 60;
        int start = rnd.next(MIN_TIME, latestStart);
        start -= start % 60;
        up = denseSchedule(upCount, start, 60);
        down = denseSchedule(downCount, start + rnd.next(0, 59), 60);
    }

    println((int)up.size(), (int)down.size());
    for (int time : up) {
        printTime(time);
    }
    for (int time : down) {
        printTime(time);
    }

    return 0;
}
