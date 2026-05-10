#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions of A: N rows, M columns
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100, "M");
    inf.readEoln();

    // Read matrix A: N lines, each with M integers
    for (int i = 0; i < N; i++) {
        vector<int> row = inf.readInts(M, -100, 100, "A");
        inf.readEoln();
        // No further checks needed per row
    }

    // Read dimensions of B: should be M rows, K columns
    int M2 = inf.readInt(1, 100, "M2");
    inf.readSpace();
    int K  = inf.readInt(1, 100, "K");
    inf.readEoln();

    // Ensure the inner dimensions match for multiplication
    ensuref(M2 == M,
            "Matrix dimension mismatch: A has %d columns but B has %d rows",
            M, M2);

    // Read matrix B: M rows, each with K integers
    for (int i = 0; i < M; i++) {
        vector<int> row = inf.readInts(K, -100, 100, "B");
        inf.readEoln();
    }

    // No extra data allowed
    inf.readEof();
    return 0;
}
