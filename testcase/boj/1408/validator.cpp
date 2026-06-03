#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int parseTime(const string& value, const char* name) {
    ensuref(value.size() == 8, "%s must have length 8", name);
    ensuref(isdigit(value[0]) && isdigit(value[1]) && value[2] == ':' &&
                isdigit(value[3]) && isdigit(value[4]) && value[5] == ':' &&
                isdigit(value[6]) && isdigit(value[7]),
            "%s must be formatted as XX:XX:XX", name);

    int hour = (value[0] - '0') * 10 + (value[1] - '0');
    int minute = (value[3] - '0') * 10 + (value[4] - '0');
    int second = (value[6] - '0') * 10 + (value[7] - '0');
    ensuref(0 <= hour && hour <= 23, "%s hour out of range: %d", name, hour);
    ensuref(0 <= minute && minute <= 59, "%s minute out of range: %d", name, minute);
    ensuref(0 <= second && second <= 59, "%s second out of range: %d", name, second);

    return hour * 3600 + minute * 60 + second;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string current = inf.readLine("[0-9:]{8}", "current");
    string start = inf.readLine("[0-9:]{8}", "start");

    int currentSeconds = parseTime(current, "current");
    int startSeconds = parseTime(start, "start");
    ensuref(currentSeconds != startSeconds, "current time and start time must differ");

    inf.readEof();
}
