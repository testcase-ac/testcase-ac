#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, A, B, M
    int N = inf.readInt(1, 50, "N");
    inf.readSpace();
    int A = inf.readInt(0, N - 1, "A");
    inf.readSpace();
    int B = inf.readInt(0, N - 1, "B");
    inf.readSpace();
    int M = inf.readInt(0, 50, "M");
    inf.readEoln();

    // Read M directed edges
    for (int i = 0; i < M; i++) {
        int u = inf.readInt(0, N - 1, "u_i");
        inf.readSpace();
        int v = inf.readInt(0, N - 1, "v_i");
        inf.readSpace();
        int cost = inf.readInt(0, 1000000, "cost_i");
        inf.readEoln();
    }

    // Read earnings for each city
    vector<int> earn = inf.readInts(N, 0, 1000000, "earn_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
