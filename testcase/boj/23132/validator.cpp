#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read K and m
    int K = inf.readInt(6, 100000, "K");
    inf.readSpace();
    long long m = inf.readLong(1LL, 1000000000000000000LL, "m");
    inf.readEoln();

    // K-1 initial nimbers a_i
    // Each a_i: 0 <= a_i < 2^32
    const long long A_UP = (1LL << 32) - 1;
    inf.readLongs(K - 1, 0LL, A_UP, "a_i");
    inf.readEoln();

    // Five coefficients b_i
    inf.readLongs(5, 0LL, A_UP, "b_i");
    inf.readEoln();

    // Five coefficients c_i
    inf.readLongs(5, 0LL, A_UP, "c_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
