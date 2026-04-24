#include "testlib.h"
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of people
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read intervals and collect all times to check uniqueness
    vector<int> times;
    times.reserve(2LL * N);

    for (int i = 0; i < N; i++) {
        // Read start and end times
        int P = inf.readInt(0, 1000000, "P_i");
        inf.readSpace();
        int Q = inf.readInt(0, 1000000, "Q_i");
        inf.readEoln();

        // Validate that P < Q
        ensuref(P < Q,
                "Invalid interval at line %d: start time P (%d) must be less than end time Q (%d)",
                i + 2, P, Q);

        times.push_back(P);
        times.push_back(Q);
    }

    // Check that no two times coincide (no start or end time overlaps any other)
    sort(times.begin(), times.end());
    for (int i = 1; i < (int)times.size(); i++) {
        ensuref(times[i] != times[i - 1],
                "Duplicate time detected: time value %d appears more than once", times[i]);
    }

    // Ensure file ends immediately after the last newline
    inf.readEof();

    return 0;
}
