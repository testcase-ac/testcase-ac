#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases, assume up to 100000 as not specified
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        // Each test case: exactly 7 natural numbers between 1 and 100
        vector<int> nums = inf.readInts(7, 1, 100, "number");
        inf.readEoln();

        // Must have at least one even number
        bool hasEven = false;
        for (int x : nums) {
            if (x % 2 == 0) {
                hasEven = true;
                break;
            }
        }
        ensuref(hasEven, "Test case %d: at least one even number is required", tc + 1);
    }

    inf.readEof();
    return 0;
}
