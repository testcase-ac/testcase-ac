#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 400, "N");
    inf.readEoln();

    // 2. Read first row (top)
    vector<int> top = inf.readInts(N, -10, 10, "top_row");
    inf.readEoln();

    // 3. Read second row (bottom)
    vector<int> bottom = inf.readInts(N, -10, 10, "bottom_row");
    inf.readEoln();

    // 4. Validate that all nonzero entries are in [-10, -1] or [1, 10]
    for (int i = 0; i < N; ++i) {
        ensuref(top[i] == 0 || (abs(top[i]) >= 1 && abs(top[i]) <= 10),
            "top_row[%d] = %d is not 0 or in [-10, -1] or [1, 10]", i, top[i]);
        ensuref(bottom[i] == 0 || (abs(bottom[i]) >= 1 && abs(bottom[i]) <= 10),
            "bottom_row[%d] = %d is not 0 or in [-10, -1] or [1, 10]", i, bottom[i]);
    }

    inf.readEof();
}
