#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    // N: 1 <= N <= 1,000,000, does not start with 0
    // K: 1 <= K <= 10

    // Read N as string to check for leading zero
    string N_str = inf.readToken("[0-9]{1,7}", "N");
    inf.readSpace();
    int K = inf.readInt(1, 10, "K");
    inf.readEoln();

    // Check N is in [1, 1000000]
    ensuref(N_str.size() >= 1 && N_str.size() <= 7, "N must have 1 to 7 digits, got %zu", N_str.size());
    ensuref(N_str[0] != '0', "N must not start with 0, got %s", N_str.c_str());
    // No unnecessary leading zeros
    if (N_str.size() > 1) {
        ensuref(N_str[0] != '0', "N must not have leading zeros, got %s", N_str.c_str());
    }
    // Check N is in range
    long long N = 0;
    for (char c : N_str) {
        N = N * 10 + (c - '0');
    }
    ensuref(1 <= N && N <= 1000000, "N must be in [1, 1000000], got %lld", N);

    inf.readEof();
}
