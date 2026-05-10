#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: 1 ≤ N ≤ 1,000,000
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    // Read M: 1 ≤ M ≤ 1,000,000, then we'll check M ≥ 2*N+1
    int M = inf.readInt(1, 1000000, "M");
    inf.readEoln();

    // Check the problem's required relation: 2N+1 ≤ M
    long long minM = 2LL * N + 1;
    ensuref((long long)M >= minM,
            "M must be at least 2*N+1, but M = %d, 2*N+1 = %lld", M, minM);

    // Read the string S of length M, consisting only of 'I' and 'O'
    string S = inf.readLine("[IO]+", "S");
    ensuref((int)S.length() == M,
            "Length of S must be exactly M: M = %d, but got %d", M, (int)S.length());

    inf.readEof();
    return 0;
}
