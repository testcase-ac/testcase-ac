#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of points
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // To ensure all x-coordinates are distinct
    set<long long> xs;

    for (int i = 1; i <= N; i++) {
        // x: coordinate, y: color
        long long x = inf.readLong(0LL, 1000000000LL, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, N, "y_i");
        inf.readEoln();

        // Check for distinct x-coordinates
        ensuref(!xs.count(x),
                "Duplicate x-coordinate at point %d: x = %lld", i, x);
        xs.insert(x);
    }

    inf.readEof();
    return 0;
}
