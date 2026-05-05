#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 50000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 50000, "M");
    inf.readEoln();

    // Read A
    string A = inf.readToken("[0-9]+", "A");
    inf.readEoln();
    ensuref((int)A.size() == N, "Length of A (%d) does not match N (%d)", (int)A.size(), N);
    ensuref(A[0] != '0' || N == 1, "A has leading zeros");

    // Read B
    string B = inf.readToken("[0-9]+", "B");
    inf.readEoln();
    ensuref((int)B.size() == M, "Length of B (%d) does not match M (%d)", (int)B.size(), M);
    ensuref(B[0] != '0' || M == 1, "B has leading zeros");

    inf.readEof();
}
