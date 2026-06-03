#include "testlib.h"
#include <algorithm>
#include <array>
#include <tuple>
#include <utility>
#include <vector>
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
    static const array<int, 13> days = {0, 31, 28, 31, 30, 31, 30,
                                        31, 31, 30, 31, 30, 31};
    if (m == 2 && isLeap(y)) {
        return 29;
    }
    return days[m];
}

bool isForbiddenToday(const Date& date) {
    return date.m == 2 && date.d == 29;
}

Date addDays(Date date, int delta) {
    while (delta > 0) {
        int leftInMonth = daysInMonth(date.y, date.m) - date.d;
        if (delta <= leftInMonth) {
            date.d += delta;
            return date;
        }
        delta -= leftInMonth + 1;
        date.d = 1;
        if (date.m == 12) {
            date.y++;
            date.m = 1;
        } else {
            date.m++;
        }
    }
    return date;
}

int daysUntilEnd(Date date) {
    int days = daysInMonth(date.y, date.m) - date.d;
    int y = date.y;
    int m = date.m + 1;
    while (y <= 9999) {
        while (m <= 12) {
            days += daysInMonth(y, m);
            m++;
        }
        y++;
        m = 1;
    }
    return days;
}

Date randomDate(int minYear, int maxYear, bool allowFeb29) {
    while (true) {
        int y = rnd.next(minYear, maxYear);
        int m = rnd.next(1, 12);
        int d = rnd.next(1, daysInMonth(y, m));
        Date date{y, m, d};
        if (allowFeb29 || !isForbiddenToday(date)) {
            return date;
        }
    }
}

Date randomTodayBefore(int maxStartYear) {
    return randomDate(1, maxStartYear, false);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    Date today{};
    Date dday{};

    if (mode == 0) {
        today = randomTodayBefore(9998);
        dday = addDays(today, rnd.next(1, 40));
    } else if (mode == 1) {
        int y = rnd.any(vector<int>{4, 100, 400, 1600, 1900, 1999, 2000,
                                    2004, 2096, 2100, 2400});
        y = min(y, 9998);
        int m = rnd.any(vector<int>{2, 2, 3, 12});
        int d = rnd.next(1, daysInMonth(y, m));
        today = Date{y, m, d};
        if (isForbiddenToday(today)) {
            today.d = rnd.next(27, 28);
        }
        dday = addDays(today, rnd.next(1, 90));
    } else if (mode == 2) {
        int y = rnd.next(1, 9998);
        today = Date{y, 12, rnd.next(25, 31)};
        dday = addDays(today, rnd.next(1, 20));
    } else if (mode == 3) {
        today = randomTodayBefore(8999);
        int extraYear = rnd.next(1000, min(9999 - today.y, 1200));
        dday = Date{today.y + extraYear, today.m, today.d};
        int extension = min(15, daysUntilEnd(dday));
        if (rnd.next(2) == 1 && extension > 0) {
            dday = addDays(dday, rnd.next(0, extension));
        }
    } else if (mode == 4) {
        today = randomTodayBefore(9000);
        int y = today.y + 999;
        int m = rnd.next(1, 12);
        int d = rnd.next(1, daysInMonth(y, m));
        dday = Date{y, m, d};
        if (tie(dday.y, dday.m, dday.d) <= tie(today.y, today.m, today.d)) {
            dday = addDays(today, rnd.next(1, 366));
        }
    } else if (mode == 5) {
        today = randomTodayBefore(9998);
        int span = rnd.next(1, min(2500, daysUntilEnd(today)));
        dday = addDays(today, span);
    } else {
        today = randomDate(9990, 9998, false);
        int maxSpan = daysUntilEnd(today);
        dday = addDays(today, rnd.next(1, maxSpan));
    }

    println(today.y, today.m, today.d);
    println(dday.y, dday.m, dday.d);
    return 0;
}
