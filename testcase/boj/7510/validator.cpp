#include "testlib.h"
#include <tuple>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    for (int tc = 1; tc <= n; tc++) {
        // Read three side lengths
        vector<int> sides = inf.readInts(3, 1, 40000, "side");
        inf.readEoln();

        int a = sides[0], b = sides[1], c = sides[2];
        // They must form a non-degenerate triangle
        ensuref(
            (long long)a + b > c && (long long)a + c > b && (long long)b + c > a,
            "Test case %d: sides (%d, %d, %d) do not satisfy triangle inequality",
            tc, a, b, c
        );
    }

    inf.readEof();
    return 0;
}
