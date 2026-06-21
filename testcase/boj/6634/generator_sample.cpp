#include "testlib.h"

#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string formatTime(int hour, int minute) {
    ostringstream out;
    out << setw(2) << setfill('0') << hour << ':' << setw(2) << setfill('0') << minute;
    return out.str();
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> times;
    set<string> used;
    auto addTime = [&](int hour, int minute) {
        string time = formatTime(hour, minute);
        if (used.insert(time).second) {
            times.push_back(time);
        }
    };

    int targetCount = rnd.next(1, 40);
    int mode = rnd.next(5);

    if (mode == 0) {
        addTime(0, 0);
        addTime(23, 59);
        addTime(rnd.next(0, 23), rnd.next(0, 59));
    } else if (mode == 1) {
        int hour = rnd.next(0, 23);
        int step = rnd.next(1, 17);
        for (int minute = rnd.next(0, step - 1); minute < 60 && (int)times.size() < targetCount; minute += step) {
            addTime(hour, minute);
        }
    } else if (mode == 2) {
        int minute = rnd.next(0, 59);
        for (int hour = rnd.next(0, 2); hour < 24 && (int)times.size() < targetCount; hour += rnd.next(1, 3)) {
            addTime(hour, minute);
        }
    } else if (mode == 3) {
        for (int digit = 0; digit <= 9 && (int)times.size() < targetCount; ++digit) {
            int hour = (digit <= 2 ? digit * 10 + rnd.next(0, digit == 2 ? 3 : 9) : rnd.next(0, 23));
            int minute = digit * 10 + rnd.next(0, 9);
            if (minute > 59) {
                minute = rnd.next(0, 59);
            }
            addTime(hour, minute);
        }
    }

    while ((int)times.size() < targetCount) {
        addTime(rnd.next(0, 23), rnd.next(0, 59));
    }

    shuffle(times.begin(), times.end());
    for (const string& time : times) {
        println(time);
    }
    println("end");

    return 0;
}
