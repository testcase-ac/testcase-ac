#include "testlib.h"

#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

struct Event {
    int day;
    int start;
    int finish;
};

int minuteAt(int hour, int minute) {
    return hour * 60 + minute;
}

int randomTime() {
    return rnd.next(0, 23 * 60 + 59);
}

int randomDay() {
    if (rnd.next(4) == 0) {
        return rnd.any(vector<int>{1, 2, 999999999, 1000000000});
    }
    return rnd.next(1, 30);
}

Event makeEvent(int mode, int day) {
    if (mode == 0) {
        int start = randomTime();
        int finish = rnd.next(start, min(23 * 60 + 59, start + rnd.next(0, 240)));
        return {day, start, finish};
    }

    if (mode == 1) {
        int base = rnd.any(vector<int>{0, minuteAt(5, 0), minuteAt(12, 0), minuteAt(23, 59)});
        int start = max(0, base - rnd.next(0, 40));
        int finish = min(23 * 60 + 59, base + rnd.next(0, 40));
        if (start > finish) {
            swap(start, finish);
        }
        return {day, start, finish};
    }

    if (mode == 2) {
        int start = rnd.next(0, 23 * 60 + 59);
        return {day, start, start};
    }

    int slot = rnd.next(0, 7);
    int start = slot * 180 + rnd.next(0, 30);
    int finish = min(23 * 60 + 59, start + rnd.next(30, 180));
    return {day, start, finish};
}

void printTime(int minutes) {
    printf("%02d%02d", minutes / 60, minutes % 60);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 5);
    println(n);

    for (int tc = 0; tc < n; ++tc) {
        int m = rnd.next(1, 18);
        vector<Event> events;
        events.reserve(m);

        int pattern = rnd.next(0, 3);
        vector<int> days;
        int dayCount = rnd.next(1, min(5, m));
        for (int i = 0; i < dayCount; ++i) {
            days.push_back(randomDay());
        }

        for (int i = 0; i < m; ++i) {
            int day = rnd.any(days);
            int mode = pattern;
            if (rnd.next(3) == 0) {
                mode = rnd.next(0, 3);
            }
            events.push_back(makeEvent(mode, day));
        }

        if (rnd.next(2) == 0) {
            shuffle(events.begin(), events.end());
        } else {
            sort(events.begin(), events.end(), [](const Event& lhs, const Event& rhs) {
                if (lhs.day != rhs.day) {
                    return lhs.day < rhs.day;
                }
                if (lhs.finish != rhs.finish) {
                    return lhs.finish < rhs.finish;
                }
                return lhs.start < rhs.start;
            });
        }

        println(m);
        for (const Event& event : events) {
            printf("%d ", event.day);
            printTime(event.start);
            printf(" ");
            printTime(event.finish);
            printf("\n");
        }
    }

    return 0;
}
