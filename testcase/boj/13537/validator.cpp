#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read sequence A of length N
    vector<long long> A = inf.readLongs(N, 1LL, 1000000000LL, "A");
    inf.readEoln();

    // Read number of queries M
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Read each query: i, j, k
    for (int q = 1; q <= M; q++) {
        int i = inf.readInt(1, N, "i");
        inf.readSpace();
        int j = inf.readInt(1, N, "j");
        inf.readSpace();
        long long k = inf.readLong(1LL, 1000000000LL, "k");
        inf.readEoln();

        ensuref(i <= j,
                "In query %d: expected i <= j but got i=%d, j=%d", 
                q, i, j);
    }

    inf.readEof();
    return 0;
}
