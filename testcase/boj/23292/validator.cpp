#include "testlib.h"

#include <set>
#include <string>

using namespace std;

struct Date {
    int year;
    int month;
    int day;
    string raw;
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

Date readDate(const string& name) {
    string raw = inf.readToken("[0-9]{8}", name);
    int year = stoi(raw.substr(0, 4));
    int month = stoi(raw.substr(4, 2));
    int day = stoi(raw.substr(6, 2));

    ensuref(1000 <= year && year <= 9999, "%s year out of range: %d", name.c_str(), year);
    ensuref(1 <= month && month <= 12, "%s month out of range: %d", name.c_str(), month);
    ensuref(1 <= day && day <= daysInMonth(year, month), "%s day out of range: %d", name.c_str(), day);

    return Date{year, month, day, raw};
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    Date birth = readDate("birth_date");
    inf.readEoln();

    int n = inf.readInt(2, 1000, "n");
    inf.readEoln();

    set<string> dates;
    for (int i = 0; i < n; ++i) {
        Date coding = readDate("coding_date");
        inf.readEoln();

        ensuref(birth.raw < coding.raw,
                "coding date must be after birth date: birth=%s coding=%s",
                birth.raw.c_str(), coding.raw.c_str());
        ensuref(dates.insert(coding.raw).second, "duplicate coding date: %s", coding.raw.c_str());
    }

    inf.readEof();
}
