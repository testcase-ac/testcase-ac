#include "testlib.h"
#include <vector>
#include <tuple>
#include <set>
using namespace std;

bool isLeap(int y) {
    if (y % 400 == 0) return true;
    if (y % 100 == 0) return false;
    return (y % 4 == 0);
}

int daysInMonth(int m, int y) {
    if (m < 1 || m > 12) return 31; // default, won't be used for valid dates
    if (m == 2) return isLeap(y) ? 29 : 28;
    if (m == 4 || m == 6 || m == 9 || m == 11) return 30;
    return 31;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int totalLines = rnd.next(8, 18); // total number of date lines (excluding terminator)

    vector<tuple<int,int,int>> dates;
    set<tuple<int,int,int>> used;

    auto addDate = [&](int d, int m, int y) {
        tuple<int,int,int> t = make_tuple(d, m, y);
        if (used.insert(t).second) {
            dates.push_back(t);
        }
    };

    // Hand-crafted important edge cases
    addDate(14, 8, 2004);  // example valid
    addDate(12, 0, 2004);  // invalid month 0
    addDate(32, 1, 1976);  // invalid day 32
    addDate(29, 2, 1974);  // non-leap year Feb 29
    addDate(29, 2, 1976);  // leap year Feb 29 (valid)
    addDate(1, 1, 1700);   // lower bound year, valid
    addDate(31, 12, 2200); // upper bound year, valid
    addDate(29, 2, 1900);  // century non-leap
    addDate(29, 2, 2000);  // century leap

    // Choose bias of valid vs invalid dates
    int patternType = rnd.next(0, 2);
    int pValid; // percentage (0..100)
    if (patternType == 0) pValid = 75;       // mostly valid
    else if (patternType == 1) pValid = 25;  // mostly invalid
    else pValid = 50;                        // balanced

    auto genValid = [&]() {
        int y = rnd.next(1700, 2200);
        int m = rnd.next(1, 12);
        int md = daysInMonth(m, y);
        int d = rnd.next(1, md);
        return make_tuple(d, m, y);
    };

    auto genInvalid = [&]() {
        int variant = rnd.next(0, 3);
        int d, m, y;
        switch (variant) {
            case 0: {
                // Invalid month (0 or 13-99)
                y = rnd.next(1700, 2200);
                if (rnd.next(0, 1) == 0) m = 0;
                else m = rnd.next(13, 99);
                d = rnd.next(0, 99);
                break;
            }
            case 1: {
                // Day 0 with valid month/year
                y = rnd.next(1700, 2200);
                m = rnd.next(1, 12);
                d = 0;
                break;
            }
            case 2: {
                // Day too large for that month, but < 100
                y = rnd.next(1700, 2200);
                m = rnd.next(1, 12);
                int md = daysInMonth(m, y);
                d = rnd.next(md + 1, 99);
                break;
            }
            default: {
                // Special: 29 Feb on a non-leap year
                do {
                    y = rnd.next(1700, 2200);
                } while (isLeap(y));
                d = 29;
                m = 2;
                break;
            }
        }
        return make_tuple(d, m, y);
    };

    // Fill up to totalLines with a mix of valid/invalid dates
    while ((int)dates.size() < totalLines) {
        bool wantValid = rnd.next(0, 99) < pValid;
        tuple<int,int,int> t = wantValid ? genValid() : genInvalid();
        addDate(get<0>(t), get<1>(t), get<2>(t));
    }

    // Output all dates
    for (auto &t : dates) {
        int d = get<0>(t), m = get<1>(t), y = get<2>(t);
        println(d, m, y);
    }

    // Terminator
    println(0, 0, 0);

    return 0;
}
