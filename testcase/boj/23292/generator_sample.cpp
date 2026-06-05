#include "testlib.h"

#include <iomanip>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Date {
    int year;
    int month;
    int day;
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

string formatDate(const Date& date) {
    ostringstream out;
    out << setfill('0') << setw(4) << date.year << setw(2) << date.month << setw(2) << date.day;
    return out.str();
}

Date randomDate(int minYear, int maxYear) {
    Date date;
    date.year = rnd.next(minYear, maxYear);
    date.month = rnd.next(1, 12);
    date.day = rnd.next(1, daysInMonth(date.year, date.month));
    return date;
}

Date nextDate(Date date) {
    ++date.day;
    if (date.day > daysInMonth(date.year, date.month)) {
        date.day = 1;
        ++date.month;
        if (date.month > 12) {
            date.month = 1;
            ++date.year;
        }
    }
    return date;
}

Date addDays(Date date, int days) {
    while (days-- > 0) {
        date = nextDate(date);
    }
    return date;
}

bool addCandidate(const Date& birth, const Date& candidate, set<string>& seen, vector<string>& dates) {
    string birthRaw = formatDate(birth);
    string raw = formatDate(candidate);
    if (candidate.year < 1000 || candidate.year > 9999 || raw <= birthRaw || seen.count(raw)) {
        return false;
    }
    seen.insert(raw);
    dates.push_back(raw);
    return true;
}

Date randomAfter(const Date& birth) {
    while (true) {
        Date candidate = randomDate(birth.year, 9999);
        if (formatDate(candidate) > formatDate(birth)) {
            return candidate;
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    Date birth;
    if (mode == 0) {
        birth = randomDate(1990, 2030);
    } else if (mode == 1) {
        vector<Date> births = {{1996, 2, 28}, {2000, 2, 29}, {2096, 12, 31}, {2400, 2, 29}};
        birth = rnd.any(births);
    } else if (mode == 2) {
        birth = randomDate(1000, 1010);
    } else if (mode == 3) {
        birth = randomDate(9980, 9998);
    } else if (mode == 4) {
        birth = randomDate(1111, 8888);
    } else {
        birth = randomDate(1000, 9990);
    }

    int n = (mode == 3 ? rnd.next(2, 8) : rnd.next(2, 30));
    set<string> seen;
    vector<string> dates;

    for (int delta = 1; delta <= 6 && static_cast<int>(dates.size()) < n; ++delta) {
        addCandidate(birth, addDays(birth, delta), seen, dates);
    }

    vector<Date> boundaryDates = {
        {9999, 12, 31}, {9999, 12, 30}, {2400, 2, 29}, {2100, 3, 1},
        {2000, 2, 29},  {2000, 3, 1},   {2030, 12, 25}, {2031, 1, 1},
    };
    shuffle(boundaryDates.begin(), boundaryDates.end());
    for (const Date& candidate : boundaryDates) {
        if (static_cast<int>(dates.size()) == n) {
            break;
        }
        addCandidate(birth, candidate, seen, dates);
    }

    while (static_cast<int>(dates.size()) < n) {
        addCandidate(birth, randomAfter(birth), seen, dates);
    }

    shuffle(dates.begin(), dates.end());

    println(formatDate(birth));
    println(n);
    for (const string& date : dates) {
        println(date);
    }

    return 0;
}
