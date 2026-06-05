#include "testlib.h"

#include <string>

using namespace std;

int readTime(const string& name) {
    string token = inf.readToken("[0-9]{4}", name);
    int hour = (token[0] - '0') * 10 + (token[1] - '0');
    int minute = (token[2] - '0') * 10 + (token[3] - '0');
    ensuref(hour <= 23, "%s hour out of range: %d in %s", name.c_str(), hour, token.c_str());
    ensuref(minute <= 59, "%s minute out of range: %d in %s", name.c_str(), minute, token.c_str());
    return hour * 60 + minute;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no test-case count limit; use the local default cap.
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    long long totalEvents = 0;
    for (int tc = 1; tc <= n; ++tc) {
        setTestCase(tc);

        int m = inf.readInt(1, 50000, "m");
        inf.readEoln();

        totalEvents += m;
        // CHECK: The statement does not cap n, so cap total event records near the
        // local practical scalar-token limit.
        ensuref(totalEvents <= 1600000, "too many total events: %lld", totalEvents);

        for (int i = 1; i <= m; ++i) {
            // CHECK: The statement says d is the day of the Olympics but gives no
            // upper bound; keep it as a positive 32-bit day index.
            inf.readInt(1, 1000000000, "d");
            inf.readSpace();
            int s = readTime("s");
            inf.readSpace();
            int e = readTime("e");
            inf.readEoln();

            // CHECK: "All events conclude the same day they started" forbids
            // crossing midnight, but does not explicitly forbid zero-duration events.
            ensuref(s <= e, "event %d ends before it starts: %d > %d", i, s, e);
        }
    }

    inf.readEof();
}
