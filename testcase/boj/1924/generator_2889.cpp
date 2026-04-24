#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> months31 = {1, 3, 5, 7, 8, 10, 12};
    vector<int> months30 = {4, 6, 9, 11};

    // Hyper-parameter for month selection
    int modeMonth = rnd.next(0, 3);
    int month;
    if (modeMonth == 0) {
        month = rnd.next(1, 12);
    } else if (modeMonth == 1) {
        month = rnd.any(months31);
    } else if (modeMonth == 2) {
        month = rnd.any(months30);
    } else {
        month = 2;
    }

    // Determine max days in selected month
    int maxDays;
    if (month == 2) {
        maxDays = 28;
    } else if (find(months30.begin(), months30.end(), month) != months30.end()) {
        maxDays = 30;
    } else {
        maxDays = 31;
    }

    // Hyper-parameter for day selection
    int modeDay = rnd.next(0, 3);
    int day;
    if (modeDay == 0) {
        day = 1;
    } else if (modeDay == 1) {
        day = maxDays;
    } else if (modeDay == 2) {
        day = rnd.wnext(maxDays, 1) + 1;   // favor larger days
    } else {
        day = rnd.wnext(maxDays, -1) + 1;  // favor smaller days
    }

    // Output a single test case
    println(month, day);
    return 0;
}
