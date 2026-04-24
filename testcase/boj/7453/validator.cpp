#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n: number of elements in each array
    int n = inf.readInt(1, 4000, "n");
    inf.readEoln();

    // Each of the next n lines contains four integers:
    // A[i], B[i], C[i], D[i], each with absolute value <= 2^28.
    const long long LIM = (1LL << 28);
    for (int i = 0; i < n; i++) {
        // readLongs reads exactly 4 space-separated longs in the given range
        vector<long long> v = inf.readLongs(4, -LIM, LIM, "value");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
