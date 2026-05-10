#include "testlib.h"
#include <string>
#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;

// Check if year is a leap year
bool is_leap(int year) {
    if (year % 4 != 0) return false;
    if (year % 100 == 0 && year % 400 != 0) return false;
    return true;
}

// Days in each month for a given year
int days_in_month(int year, int month) {
    static const int mdays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (month == 2) return is_leap(year) ? 29 : 28;
    return mdays[month-1];
}

// Add n-1 days to (y,m,d), return (yy,mm,dd)
void add_days(int& y, int& m, int& d, int n) {
    // n >= 1
    n--; // since the first day counts as day 1
    while (n > 0) {
        int dim = days_in_month(y, m);
        int rem = dim - d;
        if (n <= rem) {
            d += n;
            n = 0;
        } else {
            n -= (rem + 1);
            d = 1;
            m++;
            if (m > 12) {
                m = 1;
                y++;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read date token
    string date = inf.readToken("[0-9]{4}-[0-9]{2}-[0-9]{2}", "date");
    inf.readSpace();
    int N = inf.readInt(1, 10000, "N");
    inf.readEoln();

    // Parse date
    ensuref(date.size() == 10, "Date string length must be 10, got %zu", date.size());
    ensuref(date[4] == '-' && date[7] == '-', "Date format must be YYYY-MM-DD, got %s", date.c_str());
    string sy = date.substr(0,4);
    string sm = date.substr(5,2);
    string sd = date.substr(8,2);

    // No leading zeros for year (should be 4 digits, but 1900-2014, so always 19xx or 20xx)
    ensuref(sy[0] == '1' || sy[0] == '2', "Year must start with 1 or 2, got %s", sy.c_str());
    int year = atoi(sy.c_str());
    int month = atoi(sm.c_str());
    int day = atoi(sd.c_str());

    // Check year, month, day ranges
    ensuref(year >= 1900 && year <= 2014, "Year out of range: %d", year);
    ensuref(month >= 1 && month <= 12, "Month out of range: %d", month);
    int dim = days_in_month(year, month);
    ensuref(day >= 1 && day <= dim, "Day out of range for %04d-%02d: %d", year, month, day);

    // No unnecessary leading zeros in month and day (should be 2 digits, but 01-12 and 01-31)
    // For month
    if (month < 10) {
        ensuref(sm[0] == '0' && sm[1] == ('0'+month), "Month must be zero-padded to 2 digits: %s", sm.c_str());
    } else {
        ensuref(sm == to_string(month), "Month must be 2 digits: %s", sm.c_str());
    }
    // For day
    if (day < 10) {
        ensuref(sd[0] == '0' && sd[1] == ('0'+day), "Day must be zero-padded to 2 digits: %s", sd.c_str());
    } else {
        ensuref(sd == to_string(day), "Day must be 2 digits: %s", sd.c_str());
    }

    // Check that adding N-1 days does not overflow int (year)
    int y2 = year, m2 = month, d2 = day;
    add_days(y2, m2, d2, N);
    // No constraint on output date, but let's check that year does not overflow 32-bit int
    ensuref(y2 <= 9999, "Resulting year too large: %d", y2);

    inf.readEof();
}
