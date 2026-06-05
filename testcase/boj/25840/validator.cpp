#include "testlib.h"

#include <string>

using namespace std;

bool isValidDay(int month, int day) {
    static const int daysInMonth[] = {
        0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
    };
    return 1 <= month && month <= 12 && 1 <= day && day <= daysInMonth[month];
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        string birthday = inf.readToken("[0-9][0-9]/[0-9][0-9]", "birthday");
        inf.readEoln();

        int month = (birthday[0] - '0') * 10 + (birthday[1] - '0');
        int day = (birthday[3] - '0') * 10 + (birthday[4] - '0');
        ensuref(1 <= month && month <= 12, "invalid month at birthday %d: %s", i + 1, birthday.c_str());
        ensuref(1 <= day && day <= 31, "invalid day at birthday %d: %s", i + 1, birthday.c_str());
        ensuref(isValidDay(month, day), "invalid calendar date at birthday %d: %s", i + 1, birthday.c_str());
    }

    inf.readEof();
}
