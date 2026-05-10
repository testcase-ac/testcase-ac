#include "testlib.h"
#include <vector>
#include <queue>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int datasetCount = 0;
    while (true) {
        int m = inf.readInt(0, 100, "m");
        inf.readSpace();
        int n = inf.readInt(0, 1000, "n");
        inf.readSpace();
        int p = inf.readInt(0, 100, "p");
        inf.readEoln();

        if (m == 0 && n == 0 && p == 0) {
            // terminating line must be all zeros exactly
            break;
        }

        ++datasetCount;
        ensuref(datasetCount <= 50, "Number of datasets exceeds 50: %d", datasetCount);

        // For non-terminating dataset, parameters must satisfy the normal constraints
        ensuref(m >= 1, "For a real dataset, m must be >= 1, got %d", m);
        ensuref(p >= 1 && p <= m, "p must be in [1, m]; got p = %d, m = %d", p, m);

        vector<pair<int,int>> events;
        events.reserve(n);

        for (int i = 0; i < n; ++i) {
            int a = inf.readInt(1, m, "a_i");
            inf.readSpace();
            int b = inf.readInt(1, m, "b_i");
            inf.readEoln();

            ensuref(a != b,
                    "Self-contact is not allowed at event %d: a_i == b_i == %d",
                    i + 1, a);

            events.push_back({a, b});
        }

        // Optional global property check: simulate propagation to ensure it doesn't
        // explode beyond bounds (it can't, but this also guards logic errors if
        // someone generates malformed data).
        // Build propagation graph preserving time order.
        // As per problem, contact order matters: infection can only propagate
        // forward in time from already-infected users.
        vector<char> infected(m + 1, 0);
        infected[p] = 1;

        for (int i = 0; i < n; ++i) {
            int a = events[i].first;
            int b = events[i].second;
            bool ia = infected[a];
            bool ib = infected[b];
            if (ia && !ib) infected[b] = 1;
            else if (!ia && ib) infected[a] = 1;
            // if both infected or both not infected, nothing changes
        }

        int total = 0;
        for (int u = 1; u <= m; ++u)
            if (infected[u]) ++total;
        ensuref(total >= 1 && total <= m,
                "Computed infected count out of range: total=%d, m=%d",
                total, m);
    }

    inf.readEof();
}
