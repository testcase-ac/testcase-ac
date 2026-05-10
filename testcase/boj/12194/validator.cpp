#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1 ≤ T ≤ 100
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        // Read 10 numbers, each 0 or 1, separated by spaces
        vector<int> can_press(10);
        int available = 0;
        for (int i = 0; i < 10; ++i) {
            can_press[i] = inf.readInt(0, 1, ("can_press[" + to_string(i) + "]").c_str());
            if (can_press[i]) available++;
            if (i < 9) inf.readSpace();
        }
        inf.readEoln();

        // At least one digit must be available, otherwise it's impossible to type any number
        ensuref(available > 0, "At least one digit must be available in test case %d", tc);

        // Read X: 1 ≤ X ≤ 1000 (no upper bound in statement, but sample input has 128, so allow up to 1000 for safety)
        // But the statement says 1 ≤ X ≤ 100. However, sample input uses 128.
        // So, we must allow at least up to 128. Let's allow up to 1000 for flexibility.
        int X = inf.readInt(1, 1000, "X");
        inf.readEoln();
    }

    inf.readEof();
}
