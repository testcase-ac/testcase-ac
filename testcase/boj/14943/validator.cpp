#include "testlib.h"
#include <vector>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read L_i
    vector<int> L = inf.readInts(N, -1000, 1000, "L_i");
    inf.readEoln();

    // Check that sum of L_i is zero
    long long sum = 0;
    for (int i = 0; i < N; ++i) {
        sum += L[i];
    }
    ensuref(sum == 0, "Sum of L_i must be zero, but got %lld", sum);

    inf.readEof();
}
