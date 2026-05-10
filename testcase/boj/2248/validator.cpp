#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, L, I
    int N = inf.readInt(1, 31, "N");
    inf.readSpace();
    int L = inf.readInt(1, N, "L");
    inf.readSpace();
    long long I = inf.readLong(1LL, (1LL << N), "I");
    inf.readEoln();

    // Compute the number of N-bit binary numbers with at most L bits set to 1
    // This is sum_{k=0}^{L} C(N, k)
    long long total = 0;
    long long c = 1; // C(N, 0)
    for (int k = 0; k <= L; ++k) {
        if (k > 0) {
            c = c * (N - k + 1) / k;
        }
        total += c;
    }

    ensuref(I <= total, "I (%lld) is greater than the number of N=%d bit binary numbers with at most L=%d ones (%lld)", I, N, L, total);

    inf.readEof();
}
