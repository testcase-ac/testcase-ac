#include "testlib.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string formatClock(int minutes) {
    int hh = minutes / 60;
    int mm = minutes % 60;
    ostringstream out;
    out << setfill('0') << setw(2) << hh << ':' << setw(2) << mm;
    return out.str();
}

string formatEventTime(int millis) {
    ostringstream out;
    out << millis / 1000 << '.' << setfill('0') << setw(3) << millis % 1000;
    return out.str();
}

int itemDelta(const string& item) {
    if (item == "10MIN") return 10;
    if (item == "30MIN") return 30;
    if (item == "50MIN") return 50;
    if (item == "2HOUR") return 120;
    if (item == "4HOUR") return 240;
    return 540;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int clockMinutes = rnd.next(0, 719);
    while (clockMinutes % 10 == 0) clockMinutes = rnd.next(0, 719);
    int initialClockMinutes = clockMinutes;

    vector<int> values(6);
    vector<int> allowedValues = {1, 10, 100};
    for (int& value : values) value = rnd.any(allowedValues);

    int targetEvents = rnd.next(1, 35);
    int timeMillis = rnd.next(0, 900);
    vector<pair<int, string>> events;
    vector<bool> sealed(6, false);
    int sealedCount = 0;
    vector<string> items = {"10MIN", "30MIN", "50MIN", "2HOUR", "4HOUR", "9HOUR"};

    for (int i = 0; i < targetEvents && timeMillis < 60000 && sealedCount < 6; ++i) {
        bool useSeal = rnd.next(100) < 45;
        if (targetEvents - i <= 6 - sealedCount) useSeal = true;

        if (useSeal) {
            events.push_back({timeMillis, "^"});
            int area = clockMinutes / 120;
            if (!sealed[area]) {
                sealed[area] = true;
                ++sealedCount;
            }
        } else {
            string item = rnd.any(items);
            events.push_back({timeMillis, item});
            clockMinutes = (clockMinutes + itemDelta(item)) % 720;
        }

        timeMillis += rnd.next(1, 2500);
    }

    if (events.empty()) events.push_back({0, rnd.any(items)});

    println(formatClock(initialClockMinutes));
    println(values);
    println((int)events.size());
    for (const auto& event : events) {
        cout << formatEventTime(event.first) << ' ' << event.second << '\n';
    }

    return 0;
}
