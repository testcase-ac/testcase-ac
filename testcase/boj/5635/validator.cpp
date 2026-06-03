#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

static bool isLeapYear(int year) {
    return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}

static bool isValidDate(int day, int month, int year) {
    static const int daysInMonth[] = {
        0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
    };

    int limit = daysInMonth[month];
    if (month == 2 && isLeapYear(year)) {
        limit = 29;
    }
    return day <= limit;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    set<string> names;
    set<tuple<int, int, int>> birthdays;

    for (int i = 1; i <= n; ++i) {
        string name = inf.readToken("[A-Za-z]{1,15}", "name");
        ensuref(names.insert(name).second, "duplicate name at row %d: %s", i, name.c_str());
        inf.readSpace();

        int day = inf.readInt(1, 31, "dd");
        inf.readSpace();
        int month = inf.readInt(1, 12, "mm");
        inf.readSpace();
        int year = inf.readInt(1990, 2010, "yyyy");
        inf.readEoln();

        ensuref(isValidDate(day, month, year), "invalid date at row %d: %d %d %d", i, day, month, year);
        ensuref(birthdays.insert({year, month, day}).second,
                "duplicate birthday at row %d: %d %d %d", i, day, month, year);
    }

    inf.readEof();
}
