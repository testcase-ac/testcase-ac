#include "testlib.h"

#include <set>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "N");
    inf.readEoln();

    set<string> workers;
    for (int week = 1; week <= n; ++week) {
        vector<vector<string>> schedule(4, vector<string>(7));

        for (int shift = 0; shift < 4; ++shift) {
            for (int day = 0; day < 7; ++day) {
                schedule[shift][day] = inf.readToken("-|[a-z]{1,20}", "worker");
                if (schedule[shift][day] != "-") {
                    workers.insert(schedule[shift][day]);
                    ensuref(workers.size() <= 100,
                            "more than 100 workers appear after week %d shift %d day %d",
                            week,
                            shift + 1,
                            day + 1);
                }

                if (day + 1 < 7) {
                    inf.readSpace();
                } else {
                    inf.readEoln();
                }
            }
        }

        for (int day = 0; day < 7; ++day) {
            int filled = 0;
            for (int shift = 0; shift < 4; ++shift) {
                filled += schedule[shift][day] != "-";
            }
            ensuref(filled == 0 || filled == 4,
                    "week %d day %d has %d filled shifts, expected 0 or 4",
                    week,
                    day + 1,
                    filled);
        }
    }

    inf.readEof();
}
