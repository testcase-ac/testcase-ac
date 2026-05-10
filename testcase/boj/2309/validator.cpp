#include "testlib.h"
#include <vector>
#include <set>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read exactly 9 distinct heights, each on its own line
    vector<int> h(9);
    set<int> seen;
    for (int i = 0; i < 9; i++) {
        char buf[20];
        sprintf(buf, "height_%d", i+1);
        h[i] = inf.readInt(1, 100, buf);
        inf.readEoln();
        ensuref(!seen.count(h[i]),
                "Duplicate height detected: %d appears more than once", h[i]);
        seen.insert(h[i]);
    }

    // Verify that there is a subset of 7 dwarfs summing to 100
    long long total = 0;
    for (int x : h) total += x;
    bool ok = false;
    for (int i = 0; i < 9 && !ok; i++) {
        for (int j = i+1; j < 9; j++) {
            if (total - h[i] - h[j] == 100) {
                ok = true;
                break;
            }
        }
    }
    ensuref(ok, "No valid subset of seven dwarfs sums to 100");

    inf.readEof();
    return 0;
}
