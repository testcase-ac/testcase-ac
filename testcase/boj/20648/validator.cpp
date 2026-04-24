#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 2500, "N");
    inf.readEoln();

    // To check distinctness of x and y coordinates
    set<long long> xs, ys;

    for (int i = 1; i <= N; i++) {
        // Read coordinates
        long long x = inf.readLong(0LL, 1000000000LL, "x_i");
        inf.readSpace();
        long long y = inf.readLong(0LL, 1000000000LL, "y_i");
        inf.readEoln();

        // Ensure all x are distinct
        bool inserted_x = xs.insert(x).second;
        ensuref(inserted_x,
                "Duplicate x-coordinate at line %d: %lld",
                i + 1,  // +1 because first cow is on line 2
                x);

        // Ensure all y are distinct
        bool inserted_y = ys.insert(y).second;
        ensuref(inserted_y,
                "Duplicate y-coordinate at line %d: %lld",
                i + 1,
                y);
    }

    inf.readEof();
    return 0;
}
