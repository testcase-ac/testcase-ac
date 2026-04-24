#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Days in each month for 2015 (non-leap year)
    vector<int> days = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Category: 0 = Before, 1 = Special, 2 = After
    int cat = rnd.next(0, 2);
    int month, day;

    if (cat == 1) {
        // Exactly special day
        month = 2;
        day = 18;
    }
    else if (cat == 0) {
        // Before Feb 18: either January or early February
        if (rnd.next(0, 1) == 0) {
            month = 1;
            day = rnd.next(1, days[1]);
        } else {
            month = 2;
            day = rnd.next(1, 17);
        }
    }
    else {
        // After Feb 18: either late February or any month after
        month = rnd.next(2, 12);
        if (month == 2) {
            day = rnd.next(19, days[2]);
        } else {
            day = rnd.next(1, days[month]);
        }
    }

    // Output the month and day, each on its own line
    println(month);
    println(day);

    return 0;
}
