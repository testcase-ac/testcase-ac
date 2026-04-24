#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the total amount M: 10^9 ≤ M ≤ 10^18
    long long M = inf.readLong(1000000000LL, 1000000000000000000LL, "M");
    inf.readEoln();

    // Read the number of coin types N: 1 ≤ N ≤ 1000
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read the coin values A_i: each 1 ≤ A_i ≤ 10000
    vector<int> A = inf.readInts(N, 1, 10000, "A_i");
    inf.readEoln();

    // There must be at least one coin of value 1
    bool has_one = false;
    for (int i = 0; i < N; i++) {
        if (A[i] == 1) {
            has_one = true;
            break;
        }
    }
    ensuref(has_one, "No coin of value 1 found; the problem guarantees a 1-value coin.");

    // End of file
    inf.readEof();
    return 0;
}
