#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 500000, "N");
    inf.readEoln();

    // Read heights
    vector<int> h = inf.readInts(N, 1, 100000000, "height");
    inf.readEoln();

    // Check that all heights are distinct
    vector<int> sorted_h = h;
    sort(sorted_h.begin(), sorted_h.end());
    for (int i = 1; i < N; i++) {
        ensuref(sorted_h[i] != sorted_h[i-1],
                "Duplicate height found: height=%d at sorted positions %d and %d",
                sorted_h[i], i-1, i);
    }

    // No extra content
    inf.readEof();
    return 0;
}
