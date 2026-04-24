#include "testlib.h"
#include <string>
#include <set>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of goals
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    set<int> seen_times;
    for (int i = 1; i <= N; i++) {
        // Team number: 1 or 2
        int team = inf.readInt(1, 2, "team_i");
        inf.readSpace();

        // Time in MM:SS, two digits each
        string ts = inf.readToken("[0-9]{2}:[0-9]{2}", "time_i");
        inf.readEoln();

        // Validate format more strictly and ranges
        // ts = "MM:SS"
        int mm = (ts[0] - '0') * 10 + (ts[1] - '0');
        int ss = (ts[3] - '0') * 10 + (ts[4] - '0');
        ensuref(ts[2] == ':', "Invalid time format at line %d: '%s'", i, ts.c_str());
        ensuref(mm >= 0 && mm <= 47, "Minute out of range at line %d: %02d", i, mm);
        ensuref(ss >= 0 && ss <= 59, "Second out of range at line %d: %02d", i, ss);

        int total_sec = mm * 60 + ss;
        // Ensure no two goals at the same time
        bool inserted = seen_times.insert(total_sec).second;
        ensuref(inserted, "Duplicate score time at line %d: '%s'", i, ts.c_str());
    }

    inf.readEof();
    return 0;
}
