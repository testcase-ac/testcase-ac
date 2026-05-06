#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of already planted trees
    int N = inf.readInt(3, 100000, "N");
    inf.readEoln();

    // Read positions, one per line
    vector<long long> pos(N);
    for (int i = 0; i < N; i++) {
        pos[i] = inf.readLong(1LL, 1000000000LL, "position");
        inf.readEoln();
    }

    // Ensure strictly increasing order (distinct and sorted as per statement)
    for (int i = 1; i < N; i++) {
        ensuref(pos[i] > pos[i-1],
                "Tree positions must be strictly increasing: pos[%d]=%lld <= pos[%d]=%lld",
                i, pos[i], i-1, pos[i-1]);
    }

    inf.readEof();
    return 0;
}
