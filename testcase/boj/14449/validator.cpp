#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of cows
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read heights and ensure they are in range and distinct
    set<int> seen;
    for (int i = 0; i < N; i++) {
        int h = inf.readInt(0, 1000000000, "h_i");
        inf.readEoln();
        ensuref(!seen.count(h),
                "Duplicate height detected at position %d: %d", i+1, h);
        seen.insert(h);
    }

    // No extra data
    inf.readEof();
    return 0;
}
