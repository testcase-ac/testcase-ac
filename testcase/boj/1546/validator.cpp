#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of subjects N: 1 <= N <= 1000
    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read N scores: each between 0 and 100 inclusive
    vector<int> scores = inf.readInts(n, 0, 100, "score");
    inf.readEoln();

    // Validate that at least one score is positive
    bool anyPositive = false;
    for (int i = 0; i < n; i++) {
        if (scores[i] > 0) {
            anyPositive = true;
            break;
        }
    }
    ensuref(anyPositive,
            "At least one score must be greater than 0, but all %d scores are 0",
            n);

    inf.readEof();
    return 0;
}
