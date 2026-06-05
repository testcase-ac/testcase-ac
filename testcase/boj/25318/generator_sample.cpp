#include "testlib.h"

#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>

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

long long toSecond(const DateTime& value) {
    long long days = 0;
    for (int year = 2019; year < value.year; ++year) {
        days += isLeapYear(year) ? 366 : 365;
    }
    for (int month = 1; month < value.month; ++month) {
        days += daysInMonth(value.year, month);
    }
    days += value.day - 1;
    return days * 86400LL + value.hour * 3600LL + value.minute * 60LL +
           value.second;
}

DateTime fromSecond(long long second) {
    DateTime value{2019, 1, 1, 0, 0, 0};
    long long days = second / 86400;
    int remain = second % 86400;

    while (days >= (isLeapYear(value.year) ? 366 : 365)) {
        days -= isLeapYear(value.year) ? 366 : 365;
        ++value.year;
    }
    while (days >= daysInMonth(value.year, value.month)) {
        days -= daysInMonth(value.year, value.month);
        ++value.month;
    }
    value.day = static_cast<int>(days) + 1;
    value.hour = remain / 3600;
    remain %= 3600;
    value.minute = remain / 60;
    value.second = remain % 60;
    return value;
}

string formatDateTime(long long second) {
    DateTime value = fromSecond(second);
    char buffer[24];
    snprintf(buffer, sizeof(buffer), "%04d/%02d/%02d %02d:%02d:%02d",
             value.year, value.month, value.day, value.hour, value.minute,
             value.second);
    return buffer;
}

int ratingFor(int index, int n, int mode) {
    if (mode == 0) {
        return rnd.next(1, 30);
    }
    if (mode == 1) {
        return index % 2 == 0 ? 1 : 30;
    }
    if (mode == 2) {
        return 15 + rnd.next(-2, 2);
    }
    if (mode == 3) {
        return 1 + (index * 29) / max(1, n - 1);
    }
    return rnd.wnext(30, rnd.next(-3, 3)) + 1;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long first = toSecond({2019, 6, 6, 0, 0, 0});
    const long long leapDay = toSecond({2020, 2, 29, 0, 0, 0});
    const long long last = toSecond({2022, 7, 1, 23, 59, 59});

    int mode = rnd.next(0, 5);
    int n = 0;
    vector<long long> times;

    if (mode == 0) {
        n = 0;
    } else if (mode == 1) {
        n = rnd.next(1, 8);
        long long base = rnd.next(first, last);
        times.assign(n, base);
    } else if (mode == 2) {
        n = rnd.next(2, 14);
        times.push_back(first);
        times.push_back(last);
        for (int i = 2; i < n; ++i) {
            long long delta = rnd.next(-3 * 86400, 3 * 86400);
            times.push_back(min(last, max(first, leapDay + delta)));
        }
    } else if (mode == 3) {
        n = rnd.next(3, 24);
        long long base = rnd.next(first, last - 3600);
        for (int i = 0; i < n; ++i) {
            times.push_back(base + rnd.next(0, 3600));
        }
    } else if (mode == 4) {
        n = rnd.next(4, 40);
        long long current = rnd.next(first, first + 30LL * 86400);
        for (int i = 0; i < n; ++i) {
            times.push_back(current);
            current = min(last, current + rnd.next(0LL, 120LL * 86400));
        }
    } else {
        n = rnd.next(1, 60);
        for (int i = 0; i < n; ++i) {
            times.push_back(rnd.next(first, last));
        }
    }

    sort(times.begin(), times.end());

    println(n);
    int ratingMode = rnd.next(0, 4);
    for (int i = 0; i < n; ++i) {
        printf("%s %d\n", formatDateTime(times[i]).c_str(),
               ratingFor(i, n, ratingMode));
    }

    return 0;
}
