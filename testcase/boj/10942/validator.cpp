#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 2000, "N");
    inf.readEoln();

    // Read the sequence of N natural numbers (1 to 100000)
    vector<int> a = inf.readInts(N, 1, 100000, "a_i");
    inf.readEoln();

    // Read M, the number of queries
    int M = inf.readInt(1, 1000000, "M");
    inf.readEoln();

    // Read each query: two integers S and E with 1 ≤ S ≤ E ≤ N
    for (int i = 0; i < M; i++) {
        int S = inf.readInt(1, N, "S_i");
        inf.readSpace();
        int E = inf.readInt(S, N, "E_i");  // ensures E >= S
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
