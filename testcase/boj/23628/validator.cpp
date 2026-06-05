#include "testlib.h"

long long serialDate(int year, int month, int day) {
    return (static_cast<long long>(year) - 1) * 360 + (month - 1) * 30 + day;
}

void readDate(const char* prefix, int& year, int& month, int& day) {
    year = inf.readInt(1, 9999, format("%s_year", prefix));
    inf.readSpace();
    month = inf.readInt(1, 12, format("%s_month", prefix));
    inf.readSpace();
    day = inf.readInt(1, 30, format("%s_day", prefix));
    inf.readEoln();
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int sy, sm, sd;
    int ey, em, ed;
    readDate("S", sy, sm, sd);
    readDate("E", ey, em, ed);

    ensuref(serialDate(sy, sm, sd) < serialDate(ey, em, ed),
            "E must be later than S");

    inf.readEof();
}
