#include "testlib.h"

#include <string>
#include <tuple>

using namespace std;

struct DateTime {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

bool isLeapYear(int year) {
    return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}

int daysInMonth(int year, int month) {
    static const int days[] = {0,  31, 28, 31, 30, 31, 30,
                               31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year)) {
        return 29;
    }
    return days[month];
}

int parseTwoDigits(const string& value, int offset) {
    return (value[offset] - '0') * 10 + (value[offset + 1] - '0');
}

DateTime parseDateTime(const string& date, const string& time, int index) {
    int year = (date[0] - '0') * 1000 + (date[1] - '0') * 100 +
               (date[2] - '0') * 10 + (date[3] - '0');
    int month = parseTwoDigits(date, 5);
    int day = parseTwoDigits(date, 8);
    int hour = parseTwoDigits(time, 0);
    int minute = parseTwoDigits(time, 3);
    int second = parseTwoDigits(time, 6);

    ensuref(1 <= month && month <= 12, "invalid month at opinion %d: %02d",
            index, month);
    ensuref(1 <= day && day <= daysInMonth(year, month),
            "invalid day at opinion %d: %04d/%02d/%02d", index, year, month,
            day);
    ensuref(0 <= hour && hour <= 23, "invalid hour at opinion %d: %02d",
            index, hour);
    ensuref(0 <= minute && minute <= 59, "invalid minute at opinion %d: %02d",
            index, minute);
    ensuref(0 <= second && second <= 59, "invalid second at opinion %d: %02d",
            index, second);

    return {year, month, day, hour, minute, second};
}

tuple<int, int, int, int, int, int> asTuple(const DateTime& value) {
    return {value.year,   value.month,  value.day,
            value.hour,   value.minute, value.second};
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(0, 1000, "N");
    inf.readEoln();

    const DateTime firstAllowed = {2019, 6, 6, 0, 0, 0};
    const DateTime lastAllowed = {2022, 7, 1, 23, 59, 59};
    DateTime previous = firstAllowed;

    for (int i = 1; i <= n; ++i) {
        string date = inf.readToken("[0-9]{4}/[0-9]{2}/[0-9]{2}", "t_i_date");
        inf.readSpace();
        string time = inf.readToken("[0-9]{2}:[0-9]{2}:[0-9]{2}", "t_i_time");
        inf.readSpace();
        inf.readInt(1, 30, "l_i");
        inf.readEoln();

        DateTime current = parseDateTime(date, time, i);
        ensuref(asTuple(firstAllowed) <= asTuple(current),
                "timestamp before lower bound at opinion %d", i);
        ensuref(asTuple(current) <= asTuple(lastAllowed),
                "timestamp after upper bound at opinion %d", i);
        if (i > 1) {
            ensuref(asTuple(previous) <= asTuple(current),
                    "timestamps are not nondecreasing at opinion %d", i);
        }
        previous = current;
    }

    inf.readEof();
}
