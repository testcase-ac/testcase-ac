#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, K, M
    int N = inf.readInt(1, 50000, "N");
    inf.readSpace();
    int K = inf.readInt(1, N, "K");
    inf.readSpace();
    long long M = inf.readLong(1LL, 100000000000000LL, "M");
    inf.readEoln();

    // Read the N cows' prices and coupon prices
    for (int i = 0; i < N; i++) {
        int P = inf.readInt(1, 1000000000, "P_i");
        inf.readSpace();
        int C = inf.readInt(1, P, "C_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
