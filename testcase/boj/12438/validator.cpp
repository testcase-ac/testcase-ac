#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        long long monthCount = inf.readLong(1LL, 1000000000000LL, "month_count");
        inf.readSpace();
        int daysPerMonth = inf.readInt(1, 1000000, "days_per_month");
        inf.readSpace();
        int daysPerWeek = inf.readInt(1, 100, "days_per_week");
        inf.readEoln();

        (void)monthCount;
        (void)daysPerMonth;
        (void)daysPerWeek;
    }

    inf.readEof();
}
