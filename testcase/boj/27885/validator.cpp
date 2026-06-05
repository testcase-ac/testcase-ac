#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int parseTime(const string& value, const char* name) {
    ensuref(value[2] == ':' && value[5] == ':', "%s must use hh:mm:ss format", name);

    int hour = (value[0] - '0') * 10 + (value[1] - '0');
    int minute = (value[3] - '0') * 10 + (value[4] - '0');
    int second = (value[6] - '0') * 10 + (value[7] - '0');

    ensuref(0 <= minute && minute <= 59, "%s has invalid minute: %02d", name, minute);
    ensuref(0 <= second && second <= 59, "%s has invalid second: %02d", name, second);

    int total = hour * 3600 + minute * 60 + second;
    ensuref(5 * 3600 <= total && total < 23 * 3600 + 59 * 60 + 1,
            "%s is outside 05:00:00..23:59:00: %s", name, value.c_str());
    return total;
}

void readDirection(int count, const char* name) {
    vector<int> times;
    times.reserve(count);

    for (int i = 0; i < count; ++i) {
        string token = inf.readToken("[0-9]{2}:[0-9]{2}:[0-9]{2}", name);
        inf.readEoln();

        int current = parseTime(token, name);
        if (!times.empty()) {
            ensuref(times.back() + 60 <= current,
                    "%s train %d is less than 60 seconds after previous train", name, i + 1);
        }
        times.push_back(current);
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int c = inf.readInt(1, 600, "c");
    inf.readSpace();
    int h = inf.readInt(1, 600, "h");
    inf.readEoln();

    readDirection(c, "up_time");
    readDirection(h, "down_time");

    inf.readEof();
}
