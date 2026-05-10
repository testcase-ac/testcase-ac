#include "testlib.h"
#include <string>
#include <vector>
#include <cstdio>
using namespace std;

// Days in month for Julian/Gregorian calendar (1-based index, month 1 = January)
const int days_in_month[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

// Check if year is leap year in Julian calendar
bool is_julian_leap(int year) {
    return year % 4 == 0;
}

// Check if year is leap year in Gregorian calendar
bool is_gregorian_leap(int year) {
    if (year % 4 != 0) return false;
    if (year % 100 == 0 && year % 400 != 0) return false;
    return true;
}

// Check if the given date is valid in Julian calendar
bool is_valid_julian_date(int y, int m, int d) {
    if (m < 1 || m > 12) return false;
    int dim = days_in_month[m];
    if (m == 2 && is_julian_leap(y)) dim++;
    return d >= 1 && d <= dim;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // The problem does not specify number of test cases, so read until EOF.
    // Each line is a date in format YYYY-MM-DD, one per line.

    string line;
    int case_num = 0;
    while (!inf.seekEof()) {
        ++case_num;
        // Read line, ensure no leading/trailing whitespace
        line = inf.readLine("[^]+", "date_line");

        // Check length
        ensuref(line.size() == 10, "Line %d: Date string must be exactly 10 characters, got '%s'", case_num, line.c_str());
        // Check format: YYYY-MM-DD
        for (int i = 0; i < 10; ++i) {
            if (i == 4 || i == 7) {
                ensuref(line[i] == '-', "Line %d: Date string must have '-' at positions 5 and 8, got '%s'", case_num, line.c_str());
            } else {
                ensuref(isdigit(line[i]), "Line %d: Date string must have digits at positions other than 5 and 8, got '%s'", case_num, line.c_str());
            }
        }
        // Parse year, month, day
        int year = stoi(line.substr(0,4));
        int month = stoi(line.substr(5,2));
        int day = stoi(line.substr(8,2));

        // Range checks
        // Year: 1582-9999
        ensuref(year >= 1582 && year <= 9999, "Line %d: Year out of range [1582,9999]: %d", case_num, year);
        // Month: 1-12
        ensuref(month >= 1 && month <= 12, "Line %d: Month out of range [1,12]: %d", case_num, month);
        // Day: 1-31 (further checked below)
        ensuref(day >= 1 && day <= 31, "Line %d: Day out of range [1,31]: %d", case_num, day);

        // Check valid Julian date
        ensuref(is_valid_julian_date(year, month, day), "Line %d: Invalid Julian date: %04d-%02d-%02d", case_num, year, month, day);

        // Lower bound: no earlier than 1582-10-04
        if (year == 1582) {
            if (month < 10 || (month == 10 && day < 4)) {
                ensuref(false, "Line %d: Date is earlier than 1582-10-04: %04d-%02d-%02d", case_num, year, month, day);
            }
        }

        // Upper bound: no later than 9999-10-18
        if (year == 9999) {
            if (month > 10 || (month == 10 && day > 18)) {
                ensuref(false, "Line %d: Date is later than 9999-10-18: %04d-%02d-%02d", case_num, year, month, day);
            }
        }

        // No extra characters on the line (already checked by readLine)
        // No extra whitespace (already checked by readLine)

        // If not EOF, next line must exist
        if (!inf.seekEof()) {
            // Next character must be a new line (already consumed by readLine)
        }
    }

    inf.readEof();
}
