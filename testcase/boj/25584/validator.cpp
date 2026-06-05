#include "testlib.h"

#include <array>
#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5000, "n");
    inf.readEoln();

    set<string> workers;
    for (int week = 1; week <= n; ++week) {
        array<array<string, 7>, 4> schedule;
        for (int shift = 0; shift < 4; ++shift) {
            for (int day = 0; day < 7; ++day) {
                schedule[shift][day] = inf.readToken("-|[a-z]{1,20}", "worker");
                if (day + 1 < 7) {
                    inf.readSpace();
                } else {
                    inf.readEoln();
                }
            }
        }

        for (int day = 0; day < 7; ++day) {
            int present = 0;
            for (int shift = 0; shift < 4; ++shift) {
                if (schedule[shift][day] != "-") {
                    ++present;
                    workers.insert(schedule[shift][day]);
                }
            }
            ensuref(present == 0 || present == 4,
                    "week %d day %d must have all four shifts assigned or none",
                    week,
                    day + 1);
            ensuref(workers.size() <= 5000, "number of workers exceeds 5000");
        }
    }

    inf.readEof();
}
