#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N_MIN = 1;
    const int N_MAX = 100000;
    const long long LIM = 2147483647LL; // 2^31 - 1

    int N = inf.readInt(N_MIN, N_MAX, "N");
    inf.readSpace();
    long long M = inf.readLong(1LL, LIM, "M");
    inf.readEoln();

    long long sumW = 0;
    long long sumC = 0;

    for (int i = 0; i < N; ++i) {
        long long w = inf.readLong(0LL, LIM, "w_i");
        inf.readSpace();
        long long c = inf.readLong(0LL, LIM, "c_i");
        inf.readEoln();

        sumW += w;
        sumC += c;

        // Use 128-bit in checks to be safe from UB, but compare to LIM.
        __int128 sW = (__int128)sumW;
        __int128 sC = (__int128)sumC;
        ensuref(sW <= LIM, "Total weight exceeds 2,147,483,647 after line %d", i + 2);
        ensuref(sC <= LIM, "Total cost exceeds 2,147,483,647 after line %d", i + 2);
    }

    inf.readEof();
}
