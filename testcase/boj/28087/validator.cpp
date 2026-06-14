#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long kMaxN = 10000000LL;
    const int kMaxM = 5000000;
    const long long kMaxS = 100000000LL;

    long long n = inf.readLong(1LL, kMaxN, "N");
    inf.readSpace();
    int m = inf.readInt(1, kMaxM, "M");
    inf.readEoln();

    long long usefulSum = 0;
    const long long upper = 2 * n;
    for (int i = 1; i <= m; ++i) {
        long long s = inf.readLong(1LL, kMaxS, "S_i");
        inf.readEoln();

        if (s <= upper && usefulSum < n) {
            usefulSum += s;
            if (usefulSum > n) {
                usefulSum = n;
            }
        }
    }

    ensuref(usefulSum >= n, "no subset has total credits between N and 2N");
    inf.readEof();
}
