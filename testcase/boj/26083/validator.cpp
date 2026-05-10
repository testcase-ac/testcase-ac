#include "testlib.h"
#include <vector>
#include <string>
#include <set>
using namespace std;

// Helper: check if year, month, day is a valid date in [2000,2099]
bool is_valid_date(int y, int m, int d) {
    if (m < 1 || m > 12) return false;
    if (d < 1) return false;
    static const int mdays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int days = mdays[m-1];
    // Leap year check
    if (m == 2) {
        if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) days = 29;
    }
    if (d > days) return false;
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read today's date
    int Y = inf.readInt(0, 99, "Y");
    inf.readSpace();
    int M = inf.readInt(1, 12, "M");
    inf.readSpace();
    int D = inf.readInt(1, 31, "D");
    inf.readEoln();

    int today_year = 2000 + Y;
    int today_month = M;
    int today_day = D;
    ensuref(is_valid_date(today_year, today_month, today_day),
        "Today's date is not a valid date: %d/%d/%d", today_year, today_month, today_day);

    // Read N
    int N = inf.readInt(1, 300000, "N");
    inf.readEoln();

    for (int i = 0; i < N; ++i) {
        int A = inf.readInt(0, 99, "A");
        inf.readSpace();
        int B = inf.readInt(0, 99, "B");
        inf.readSpace();
        int C = inf.readInt(0, 99, "C");
        inf.readEoln();

        // No further constraints on A,B,C in input
        // All are in [0,99]
    }

    inf.readEof();
}
