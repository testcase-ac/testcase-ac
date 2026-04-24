#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read Ulrim Geminis scores for innings 1 to 9
    vector<int> a = inf.readInts(9, 0, 20, "a_i");
    inf.readEoln();

    // Read Startlink Gullivers scores for innings 1 to 9
    vector<int> b = inf.readInts(9, 0, 20, "b_i");
    inf.readEoln();

    // Sum the scores
    long long sumA = 0, sumB = 0;
    for (int i = 0; i < 9; i++) {
        sumA += a[i];
        sumB += b[i];
    }

    // The problem guarantees that team B's total is strictly greater than team A's
    ensuref(sumB > sumA,
            "Total score of team B must be greater than team A (got sumB=%lld, sumA=%lld)",
            sumB, sumA);

    inf.readEof();
    return 0;
}
