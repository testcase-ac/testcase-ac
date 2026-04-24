#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read K: total kunas to distribute
    long long K = inf.readLong(100LL, 1000000LL, "K");
    inf.readEoln();

    // Read N: number of projects
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // To give N distinct positive integers summing to K, we need at least 1+2+...+N
    long long min_sum = (long long)N * (N + 1) / 2;
    ensuref(min_sum <= K,
            "Not enough K for distinct positive distribution: need at least %lld, but K = %lld",
            min_sum, K);

    inf.readEof();
    return 0;
}
