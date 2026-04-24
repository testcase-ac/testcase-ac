#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read grid dimensions
    int N = inf.readInt(1, 50, "N");
    inf.readSpace();
    int M = inf.readInt(1, 50, "M");
    inf.readEoln();

    // Read each row and validate
    for (int i = 0; i < N; i++) {
        // Read a token consisting only of '.' or 'X'
        string row = inf.readToken("[.X]+", "row");
        // Check exact length M
        ensuref((int)row.length() == M,
                "Row %d: expected length %d, but got %d",
                i + 1, M, (int)row.length());
        inf.readEoln();
    }

    // No extra data allowed
    inf.readEof();
    return 0;
}
