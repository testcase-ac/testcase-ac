#include "testlib.h"
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 300000, "N");
    inf.readSpace();
    // We know K <= 2*N and N <= 300000, so K_max = 600000
    int K = inf.readInt(1, 600000, "K");
    ensuref(K <= 2LL * N, "K must be at most 2*N, but K=%d and N=%d", K, N);
    inf.readEoln();

    // Read the N integers, each |X_i| <= 1e9
    vector<long long> X = inf.readLongs(N, -1000000000LL, 1000000000LL, "X_i");
    inf.readEoln();

    // No further global properties to check for validator:
    // - Xi may be zero or negative per problem statement.
    // - K in [1,2N], N in [1,300k].

    inf.readEof();
    return 0;
}
