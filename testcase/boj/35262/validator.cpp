#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K with constraints and canonical integer form
    int N = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int K = inf.readInt(1, N, "K");
    inf.readEoln();

    // Read the binary sequence as a token of length exactly N, consisting of '0' and '1'
    string s = inf.readToken("[01]{1,1000000}", "visits");
    inf.readEoln();

    ensuref((int)s.size() == N,
            "Length of visits string (%d) must be exactly N (%d)", (int)s.size(), N);

    // No further semantic/global constraints are specified that must hold for all inputs.
    // The condition about "if there exists a period ..." is part of the solution logic,
    // not an input guarantee, so we do not enforce it here.

    inf.readEof();
}
