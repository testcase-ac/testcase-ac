#include "testlib.h"
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 100000;
    const int MAXT = 1000000000;

    int n = inf.readInt(1, MAXN, "N");
    inf.readEoln();

    vector<int> seen(n + 1, 0);

    for (int i = 0; i < n; ++i) {
        int id = inf.readInt(1, n, "lecture_id");
        inf.readSpace();
        int s = inf.readInt(0, MAXT, "start_time");
        inf.readSpace();
        int e = inf.readInt(0, MAXT, "end_time");
        inf.readEoln();

        ensuref(s < e, "Lecture %d has invalid times: start_time (%d) must be < end_time (%d)", id, s, e);

        ensuref(!seen[id], "Lecture id %d appears more than once", id);
        seen[id] = 1;
    }

    // Ensure every id from 1..N appears exactly once.
    for (int id = 1; id <= n; ++id) {
        ensuref(seen[id], "Lecture id %d is missing from input", id);
    }

    inf.readEof();
}
