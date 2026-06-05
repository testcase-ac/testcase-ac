#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxTime = 2147483647;

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    set<int> endpoints;
    for (int i = 0; i < n; ++i) {
        int start = inf.readInt(0, maxTime, "start");
        inf.readSpace();
        int end = inf.readInt(0, maxTime, "end");
        inf.readSpace();
        int people = inf.readInt(1, 1000, "people");
        inf.readEoln();

        ensuref(start < end, "meeting %d has start >= end: %d >= %d", i + 1, start, end);
        ensuref(endpoints.insert(start).second, "duplicate start/end time at meeting %d: %d", i + 1, start);
        ensuref(endpoints.insert(end).second, "duplicate start/end time at meeting %d: %d", i + 1, end);
        (void)people;
    }

    inf.readEof();
}
