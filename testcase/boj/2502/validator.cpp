#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read D and K with their constraints
    int D = inf.readInt(3, 30, "D");
    inf.readSpace();
    int K = inf.readInt(10, 100000, "K");
    inf.readEoln();

    // Compute the Fibonacci-like coefficients:
    // Day 1 = A, Day 2 = B, Day i = Day_(i-1) + Day_(i-2)
    // So for day D: K = f[D-2] * A + f[D-1] * B
    vector<long long> f(D+1);
    f[1] = 1;
    f[2] = 1;
    for (int i = 3; i <= D; i++) {
        f[i] = f[i-1] + f[i-2];
    }
    long long coeffA = f[D-2];
    long long coeffB = f[D-1];

    // Verify that there exists integers A, B with 1 <= A <= B such that
    // coeffA * A + coeffB * B = K
    bool found = false;
    // A must satisfy A >= 1 and A * coeffA <= K
    for (long long A = 1; A * coeffA <= K; A++) {
        long long rem = K - A * coeffA;
        if (rem % coeffB != 0) continue;
        long long B = rem / coeffB;
        if (B >= A) {
            found = true;
            break;
        }
    }
    ensuref(found, "No valid A, B exist for D=%d, K=%d", D, K);

    inf.readEof();
    return 0;
}
