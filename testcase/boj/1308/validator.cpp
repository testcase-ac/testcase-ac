#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Date {
    int y;
    int m;
    int d;
};

bool isLeap(int y) {
    return y % 400 == 0 || (y % 4 == 0 && y % 100 != 0);
}

int daysInMonth(int y, int m) {
    static const int days[] = {0, 31, 28, 31, 30, 31, 30,
                               31, 31, 30, 31, 30, 31};
    if (m == 2 && isLeap(y)) {
        return 29;
    }
    return days[m];
}

bool isValidDate(const Date& date) {
    return 1 <= date.m && date.m <= 12 &&
           1 <= date.d && date.d <= daysInMonth(date.y, date.m);
}

bool before(const Date& a, const Date& b) {
    return tie(a.y, a.m, a.d) < tie(b.y, b.m, b.d);
}

Date readDate(const string& prefix) {
    Date date;
    date.y = inf.readInt(1, 9999, prefix + "_year");
    inf.readSpace();
    date.m = inf.readInt(1, 12, prefix + "_month");
    inf.readSpace();
    date.d = inf.readInt(1, 31, prefix + "_day");
    inf.readEoln();
    ensuref(isValidDate(date), "%s is not a valid date: %04d-%02d-%02d",
            prefix.c_str(), date.y, date.m, date.d);
    return date;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    Date today = readDate("today");
    Date dday = readDate("dday");

    ensuref(!(today.m == 2 && today.d == 29),
            "today must not be February 29");
    ensuref(before(today, dday), "today must be before dday");

    inf.readEof();
}
