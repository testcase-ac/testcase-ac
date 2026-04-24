#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read A and B, check they're within 32-bit signed integer range
    long long A = inf.readLong(-2147483648LL, 2147483647LL, "A");
    inf.readSpace();
    long long B = inf.readLong(-2147483648LL, 2147483647LL, "B");
    inf.readEoln();

    // Compute number of terms: |B - A| + 1
    __int128 diff = (__int128)B - A;
    if (diff < 0) diff = -diff;
    __int128 terms = diff + 1;

    // Compute sum = (A + B) * terms / 2 using 128-bit to avoid overflow
    __int128 sum = (__int128)(A + B) * terms;
    // Since sum must be integer, divide by 2
    // (Guaranteed to be divisible by 2 for integer sequence sums)
    sum /= 2;

    // Validate that the result fits in 32-bit signed integer, as stated in problem
    ensuref(
        sum >= -2147483648LL && sum <= 2147483647LL,
        "Sum of all integers between A=%lld and B=%lld is %lld, which is out of the 32-bit signed integer range",
        A, B, (long long)sum
    );

    inf.readEof();
    return 0;
}
