#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions N and M
    int N = inf.readInt(1, 14, "N");
    inf.readSpace();
    int M = inf.readInt(1, 14, "M");
    inf.readEoln();

    // Read grid rows
    for (int i = 0; i < N; i++) {
        // Each row is exactly M characters from the set {A, B, C, D, F}
        // We read as a token without whitespace
        string row = inf.readToken("[ABCDF]{1,14}", "row");
        ensuref((int)row.size() == M,
                "Length of row %d must be exactly M=%d, but got %d characters",
                i + 1, M, (int)row.size());
        inf.readEoln();
    }

    // No extra content
    inf.readEof();
    return 0;
}
