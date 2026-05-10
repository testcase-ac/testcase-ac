#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N as string to check for leading zeros, then parse as long long
    string N_str = inf.readToken("[0-9]+", "N");
    inf.readEoln();

    // Check for leading zeros (except for "0" itself, but N >= 1)
    ensuref(N_str.size() == 1 || N_str[0] != '0', "N has unnecessary leading zeros: %s", N_str.c_str());

    // Parse N and check bounds
    long long N = 0;
    for (char c : N_str) {
        N = N * 10 + (c - '0');
        // Early check for overflow
        ensuref(N <= 1000000000000000000LL, "N exceeds upper bound after parsing: %s", N_str.c_str());
    }
    ensuref(1 <= N && N <= 1000000000000000000LL, "N is out of bounds: %lld", N);

    inf.readEof();
}
