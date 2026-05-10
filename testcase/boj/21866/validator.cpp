#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxPerProblem[9] = {100, 100, 200, 200, 300, 300, 400, 400, 500};

    long long sum = 0;
    bool hacker = false;

    for (int i = 0; i < 9; ++i) {
        int x = inf.readInt(0, 1000, "score");
        if (i + 1 < 9) inf.readSpace();
        sum += x;
        if (x > maxPerProblem[i]) hacker = true;
    }
    inf.readEoln();

    // Check that the output classification is always well-defined as per problem:
    // - If any score exceeds its max, student is hacker (regardless of sum).
    // - Else if sum >= 100, student is draw (coffee draw candidate).
    // - Else none.
    // Since we don't have the solution output in the input file, we can only
    // ensure that these categories are mutually exclusive and exhaustive
    // for any valid input; no additional structural/global constraints needed.
    // Still, we can assert the internal logic here for sanity.
    if (hacker) {
        // hacker status overrides sum condition; nothing else to check
    } else {
        // not hacker: sum must be in [0, 9*1000] automatically by bounds.
        ensuref(sum >= 0 && sum <= 9000,
                "Sum of scores out of expected computed bounds: %lld", sum);
    }

    inf.readEof();
}
