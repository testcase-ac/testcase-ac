#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: order of the Fibonacci tree, 0 <= N <= 50
    int N = inf.readInt(0, 50, "N");
    inf.readSpace();

    // Read start and end positions: 1 <= pos <= 1e9
    long long start = inf.readLong(1LL, 1000000000LL, "start");
    inf.readSpace();
    long long endpos = inf.readLong(1LL, 1000000000LL, "end");
    inf.readEoln();

    // Precompute number of nodes in Fibonacci trees up to N=50
    vector<unsigned long long> F(51);
    F[0] = 1;
    F[1] = 1;
    for (int i = 2; i <= 50; i++) {
        // F[i] = 1 (root) + nodes of F[i-1] on right + nodes of F[i-2] on left
        F[i] = 1ULL + F[i-1] + F[i-2];
    }

    unsigned long long maxNodes = F[N];
    ensuref((unsigned long long)start <= maxNodes,
            "start (%lld) is greater than number of nodes (%llu) in Fibonacci tree of order %d",
            start, maxNodes, N);
    ensuref((unsigned long long)endpos <= maxNodes,
            "end (%lld) is greater than number of nodes (%llu) in Fibonacci tree of order %d",
            endpos, maxNodes, N);

    // Finish: exactly one newline after input line, then EOF
    inf.readEof();
    return 0;
}
