#include "testlib.h"

#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 5000, "N");
    inf.readEoln();

    vector<int> days(n);
    set<int> diffs;
    for (int i = 0; i < n; ++i) {
        days[i] = inf.readInt(1, 999999999, "day_i");
        inf.readEoln();

        if (i == 0) {
            ensuref(days[i] == 1, "first day must be 1, found %d", days[i]);
        } else {
            ensuref(days[i - 1] < days[i],
                    "days must be strictly increasing at index %d: %d >= %d",
                    i + 1, days[i - 1], days[i]);
            diffs.insert(days[i] - 1);
        }
    }

    const int todayDiff = days.back() - 1;
    vector<int> validPeriods;
    for (int period : diffs) {
        bool valid = true;
        for (long long multiple = period; multiple <= todayDiff; multiple += period) {
            if (!diffs.count(static_cast<int>(multiple))) {
                valid = false;
                break;
            }
        }
        if (valid) {
            validPeriods.push_back(period);
        }
    }

    for (int diff : diffs) {
        bool covered = false;
        for (int period : validPeriods) {
            if (period > diff) {
                break;
            }
            if (diff % period == 0) {
                covered = true;
                break;
            }
        }
        ensuref(covered, "day %d cannot be produced by any valid ship period", diff + 1);
    }

    inf.readEof();
}
