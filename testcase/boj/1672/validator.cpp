#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and validate its range
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    // Read the DNA sequence and validate characters
    string s = inf.readToken("[ACGT]+", "sequence");
    // Ensure the length matches N exactly
    ensuref((int)s.size() == N,
            "Length of DNA sequence (%d) does not match N (%d)", (int)s.size(), N);
    inf.readEoln();

    // No extra data after this
    inf.readEof();
    return 0;
}
