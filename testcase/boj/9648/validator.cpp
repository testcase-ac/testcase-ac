#include "testlib.h"
#include <cctype>
#include <cstdio>
#include <string>
using namespace std;

const int days_in_month[13] = {0, 31, 28, 31, 30, 31, 30,
                               31, 31, 30, 31, 30, 31};

bool is_julian_leap(int year) {
    return year % 4 == 0;
}

bool is_valid_julian_date(int y, int m, int d) {
    if (m < 1 || m > 12) return false;
    int dim = days_in_month[m];
    if (m == 2 && is_julian_leap(y)) dim++;
    return d >= 1 && d <= dim;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int case_num = 0;
    while (!inf.eof()) {
        ++case_num;
        string line = inf.readLine("[0-9]{4}-[0-9]{2}-[0-9]{2}", "date_line");

        for (int i = 0; i < 10; ++i) {
            if (i == 4 || i == 7) {
                ensuref(line[i] == '-', "Line %d: Date string must have '-' at positions 5 and 8, got '%s'", case_num, line.c_str());
            } else {
                ensuref(isdigit(line[i]), "Line %d: Date string must have digits at positions other than 5 and 8, got '%s'", case_num, line.c_str());
            }
        }

        int year = (line[0] - '0') * 1000 + (line[1] - '0') * 100 +
                   (line[2] - '0') * 10 + (line[3] - '0');
        int month = (line[5] - '0') * 10 + (line[6] - '0');
        int day = (line[8] - '0') * 10 + (line[9] - '0');

        ensuref(year >= 1582 && year <= 9999, "Line %d: Year out of range [1582,9999]: %d", case_num, year);
        ensuref(month >= 1 && month <= 12, "Line %d: Month out of range [1,12]: %d", case_num, month);
        ensuref(day >= 1 && day <= 31, "Line %d: Day out of range [1,31]: %d", case_num, day);
        ensuref(is_valid_julian_date(year, month, day), "Line %d: Invalid Julian date: %04d-%02d-%02d", case_num, year, month, day);

        if (year == 1582) {
            if (month < 10 || (month == 10 && day < 4)) {
                ensuref(false, "Line %d: Date is earlier than 1582-10-04: %04d-%02d-%02d", case_num, year, month, day);
            }
        }

        if (year == 9999) {
            if (month > 10 || (month == 10 && day > 18)) {
                ensuref(false, "Line %d: Date is later than 9999-10-18: %04d-%02d-%02d", case_num, year, month, day);
            }
        }
    }

    ensuref(case_num >= 1, "Input must contain at least one date line");
    inf.readEof();
}
