#include "testlib.h"

#include <algorithm>

using namespace std;

struct Date {
    int year;
    int month;
    int day;
};

long long serialDate(const Date& date) {
    return (static_cast<long long>(date.year) - 1) * 360 +
           (date.month - 1) * 30 + date.day;
}

Date fromSerial(long long serial) {
    --serial;
    Date date;
    date.year = static_cast<int>(serial / 360) + 1;
    serial %= 360;
    date.month = static_cast<int>(serial / 30) + 1;
    date.day = static_cast<int>(serial % 30) + 1;
    return date;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long minSerial = 1;
    const long long maxSerial = 9999LL * 360;

    int mode = rnd.next(0, 7);
    long long start = minSerial;
    long long gap = 1;

    if (mode == 0) {
        gap = rnd.next(1, 29);
        start = rnd.next(minSerial, maxSerial - gap);
    } else if (mode == 1) {
        gap = 30LL * rnd.next(1, 36);
        start = rnd.next(minSerial, maxSerial - gap);
    } else if (mode == 2) {
        gap = 360LL * rnd.next(1, 20);
        start = rnd.next(minSerial, maxSerial - gap);
    } else if (mode == 3) {
        int years = rnd.next(1, 200);
        int extraMonths = rnd.next(0, 11);
        int extraDays = rnd.next(0, 29);
        gap = 360LL * years + 30LL * extraMonths + extraDays;
        start = rnd.next(minSerial, maxSerial - gap);
    } else if (mode == 4) {
        Date date{rnd.next(1, 9998), rnd.next(1, 12), rnd.next(0, 1) == 0 ? 1 : 30};
        start = serialDate(date);
        gap = rnd.next(1LL, min(720LL, maxSerial - start));
    } else if (mode == 5) {
        start = rnd.next(minSerial, minSerial + 720);
        gap = rnd.next(1LL, maxSerial - start);
    } else if (mode == 6) {
        long long end = rnd.next(maxSerial - 720, maxSerial);
        start = rnd.next(minSerial, end - 1);
        gap = end - start;
    } else {
        start = rnd.next(minSerial, maxSerial - 1);
        gap = rnd.next(1LL, min(5000LL, maxSerial - start));
    }

    Date s = fromSerial(start);
    Date e = fromSerial(start + gap);

    println(s.year, s.month, s.day);
    println(e.year, e.month, e.day);

    return 0;
}
