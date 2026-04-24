#include "testlib.h"
#include <set>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of plants
    int N = inf.readInt(1, 300000, "N");
    inf.readEoln();

    // Check distinct coordinates
    set<uint64_t> seen;
    seen.clear();

    for (int i = 0; i < N; i++) {
        int x = inf.readInt(0, 1000000000, "x_i");
        inf.readSpace();
        int y = inf.readInt(0, 1000000000, "y_i");
        inf.readEoln();

        uint64_t key = (uint64_t(x) << 32) | uint32_t(y);
        ensuref(!seen.count(key),
                "Duplicate coordinate at line %d: (%d, %d)",
                i + 2, x, y);
        seen.insert(key);
    }

    inf.readEof();
    return 0;
}
