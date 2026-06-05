#include "testlib.h"
#include <string>
using namespace std;

int monthIndex(int year, int month) {
    return year * 12 + month;
}

pair<int, int> readYearMonth(const string& name) {
    string value = inf.readToken("[0-9]{4}-[0-9]{2}", name);

    int year = stoi(value.substr(0, 4));
    int month = stoi(value.substr(5, 2));
    ensuref(2000 <= year && year <= 9999, "%s year out of range: %d",
            name.c_str(), year);
    ensuref(1 <= month && month <= 12, "%s month out of range: %d",
            name.c_str(), month);

    return {year, month};
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        auto [startYear, startMonth] = readYearMonth("start");
        inf.readSpace();
        auto [endYear, endMonth] = readYearMonth("end");
        inf.readEoln();

        int start = monthIndex(startYear, startMonth);
        int end = monthIndex(endYear, endMonth);
        ensuref(start <= end,
                "end month is before enlistment month at friend %d", i + 1);
    }

    inf.readEof();
    return 0;
}
