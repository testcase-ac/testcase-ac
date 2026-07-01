#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int parseTime(const string& value, const string& name) {
    ensuref(value.size() == 5, "%s must have length 5: %s", name.c_str(), value.c_str());
    ensuref(value[2] == ':', "%s must contain ':' at index 3: %s", name.c_str(), value.c_str());
    ensuref('0' <= value[0] && value[0] <= '9', "%s hour tens is not a digit: %s", name.c_str(), value.c_str());
    ensuref('0' <= value[1] && value[1] <= '9', "%s hour ones is not a digit: %s", name.c_str(), value.c_str());
    ensuref('0' <= value[3] && value[3] <= '9', "%s minute tens is not a digit: %s", name.c_str(), value.c_str());
    ensuref('0' <= value[4] && value[4] <= '9', "%s minute ones is not a digit: %s", name.c_str(), value.c_str());

    int hour = (value[0] - '0') * 10 + (value[1] - '0');
    int minute = (value[3] - '0') * 10 + (value[4] - '0');
    ensuref(0 <= hour && hour <= 23, "%s hour out of range: %s", name.c_str(), value.c_str());
    ensuref(0 <= minute && minute <= 59, "%s minute out of range: %s", name.c_str(), value.c_str());
    return hour * 60 + minute;
}

void readTrains(int count, int expectedParity, const string& direction) {
    int previousNumber = -1;
    vector<bool> seenStart(24 * 60, false);

    for (int i = 1; i <= count; ++i) {
        int number = inf.readInt(100, 999, (direction + "_number").c_str());
        ensuref(number % 2 == expectedParity,
                "%s train %d has wrong parity: %d",
                direction.c_str(), i, number);
        ensuref(previousNumber < number,
                "%s train numbers must increase with departure order at index %d: previous=%d current=%d",
                direction.c_str(), i, previousNumber, number);
        previousNumber = number;

        inf.readSpace();
        string start = inf.readToken("[0-9]{2}:[0-9]{2}", (direction + "_start").c_str());
        int minutes = parseTime(start, direction + "_start");
        ensuref(!seenStart[minutes],
                "%s trains must not share a departure time: %s",
                direction.c_str(), start.c_str());
        seenStart[minutes] = true;
        inf.readEoln();
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int c = inf.readInt(1, 20, "C");
    inf.readSpace();
    int h = inf.readInt(1, 20, "H");
    inf.readEoln();

    readTrains(c, 1, "down");
    readTrains(h, 0, "up");

    inf.readEof();
}
