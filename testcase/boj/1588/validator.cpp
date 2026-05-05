#include "testlib.h"
#include <climits>
#include <cmath>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: initial number (1, 2, or 3)
    int initial = inf.readInt(1, 3, "initial");
    inf.readEoln();

    // Second line: Left (0 <= Left)
    long long Left = inf.readLong(0LL, 2147483647LL, "Left");
    inf.readEoln();

    // Third line: Right (Left <= Right <= 2147483647)
    long long Right = inf.readLong(Left, 2147483647LL, "Right");
    inf.readEoln();

    // Fourth line: N (0 <= N <= 20)
    int N = inf.readInt(0, 20, "N");
    inf.readEoln();

    // Compute 3^N safely (N <= 20, so fits in long long)
    long long max_index = 1;
    for (int i = 0; i < N; ++i) {
        max_index *= 3LL;
    }
    max_index--; // 3^N - 1

    // Now, Right must be <= min(2147483647, 3^N-1)
    long long max_allowed = std::min(2147483647LL, max_index);

    ensuref(Right <= max_allowed, 
        "Right (%lld) must be <= min(2147483647, 3^N-1) = %lld", Right, max_allowed);
    ensuref(Left <= Right, "Left (%lld) must be <= Right (%lld)", Left, Right);

    inf.readEof();
}
