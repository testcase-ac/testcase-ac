#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // Read input
    int T = inf.readInt();
    int N = inf.readInt();
    vector<int> r(N);
    for (int i = 0; i < N; i++) {
        r[i] = inf.readInt();
    }

    // Read contestant's answer: N start times
    vector<int> S(N);
    for (int i = 0; i < N; i++) {
        // Each start time must be between 0 and T - r[i]
        S[i] = ouf.readInt(0, T - r[i], format("start time for member %d", i+1).c_str());
    }
    // No extra output allowed
    ouf.readEof();

    // Sweep-line to count number of simultaneous rests
    // We consider intervals [S[i], S[i] + r[i]) for each member i.
    vector<int> event(T+1, 0);
    for (int i = 0; i < N; i++) {
        int start = S[i];
        int len   = r[i];
        // Double-check bounds
        if (start < 0 || start > T - len) {
            ouf.quitf(_wa, "start time for member %d is invalid: %d", i+1, start);
        }
        event[start]++;
        event[start + len]--;
    }

    int cur = 0;
    // Check at each minute t in [0, T) that no more than 2 members are resting
    for (int t = 0; t < T; t++) {
        cur += event[t];
        if (cur > 2) {
            quitf(_wa, "more than two members resting at time %d", t);
        }
    }

    // If all checks passed, accept
    quitf(_ok, "valid schedule");
}
