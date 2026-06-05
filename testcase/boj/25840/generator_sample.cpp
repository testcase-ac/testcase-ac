#include "testlib.h"

#include <cstdio>
#include <string>
#include <vector>

using namespace std;

int daysInMonth(int month) {
    static const int days[] = {
        0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
    };
    return days[month];
}

string formatDate(int month, int day) {
    char buffer[6];
    snprintf(buffer, sizeof(buffer), "%02d/%02d", month, day);
    return string(buffer);
}

vector<string> allDates() {
    vector<string> dates;
    for (int month = 1; month <= 12; ++month) {
        for (int day = 1; day <= daysInMonth(month); ++day) {
            dates.push_back(formatDate(month, day));
        }
    }
    return dates;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> dates = allDates();
    shuffle(dates.begin(), dates.end());

    int mode = rnd.next(0, 5);
    vector<string> birthdays;

    if (mode == 0) {
        int n = rnd.next(1, 12);
        birthdays.assign(dates.begin(), dates.begin() + n);
    } else if (mode == 1) {
        int distinct = rnd.next(1, 6);
        int n = rnd.next(distinct, 20);
        vector<string> pool(dates.begin(), dates.begin() + distinct);
        for (int i = 0; i < n; ++i) {
            birthdays.push_back(rnd.any(pool));
        }
    } else if (mode == 2) {
        int month = rnd.next(1, 12);
        int n = rnd.next(2, 20);
        for (int i = 0; i < n; ++i) {
            birthdays.push_back(formatDate(month, rnd.next(1, daysInMonth(month))));
        }
    } else if (mode == 3) {
        vector<string> pool = {
            "02/27", "02/28", "02/29", "03/01", "04/30", "12/31", "01/01",
        };
        int n = rnd.next(1, 25);
        for (int i = 0; i < n; ++i) {
            birthdays.push_back(rnd.any(pool));
        }
    } else if (mode == 4) {
        int n = rnd.next(25, 50);
        for (int i = 0; i < n; ++i) {
            birthdays.push_back(rnd.any(dates));
        }
    } else {
        int distinct = rnd.next(2, 15);
        int n = rnd.next(distinct, 50);
        vector<string> pool(dates.begin(), dates.begin() + distinct);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                birthdays.push_back(rnd.any(pool));
            } else {
                birthdays.push_back(pool[i % distinct]);
            }
        }
        shuffle(birthdays.begin(), birthdays.end());
    }

    println((int)birthdays.size());
    for (const string& birthday : birthdays) {
        println(birthday);
    }

    return 0;
}
