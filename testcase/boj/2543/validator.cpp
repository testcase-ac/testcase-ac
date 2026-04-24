#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of robots
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    vector<int> endpoints;
    endpoints.reserve(2 * N);

    for (int i = 0; i < N; i++) {
        int l = inf.readInt(0, 10000000, "l_i");
        inf.readSpace();
        int r = inf.readInt(0, 10000000, "r_i");
        inf.readEoln();

        ensuref(l < r,
                "Interval %d has left endpoint (%d) not less than right endpoint (%d)",
                i+1, l, r);

        endpoints.push_back(l);
        endpoints.push_back(r);
    }

    // Check that all endpoints are distinct
    sort(endpoints.begin(), endpoints.end());
    for (int i = 1; i < (int)endpoints.size(); i++) {
        ensuref(endpoints[i] != endpoints[i-1],
                "Duplicate endpoint coordinate detected: %d",
                endpoints[i]);
    }

    inf.readEof();
    return 0;
}
