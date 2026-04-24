#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    // We'll track seen values in range [-1e6, 1e6]
    const int OFFSET = 1000000;
    const int RANGE = 2 * OFFSET + 1;
    vector<char> seen(RANGE, 0);

    // Read N distinct integers, one per line
    for (int i = 0; i < N; i++) {
        int x = inf.readInt(-1000000, 1000000, "value");
        inf.readEoln();
        int idx = x + OFFSET;
        ensuref(!seen[idx],
                "Duplicate number at line %d: %d", 
                i + 2, // +2 because line 1 is N, lines 2..N+1 are values
                x);
        seen[idx] = 1;
    }

    // No extra data
    inf.readEof();
    return 0;
}
