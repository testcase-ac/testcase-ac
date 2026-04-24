#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions
    int N = inf.readInt(1, 50, "N");
    inf.readSpace();
    int M = inf.readInt(1, 50, "M");
    inf.readEoln();

    // Prepare regex for a row of length M consisting of '0' or '1'
    string row_regex = string("[01]{") + to_string(M) + "}";

    // Read matrix A
    for (int i = 0; i < N; i++) {
        inf.readToken(row_regex, "A_row");
        inf.readEoln();
    }

    // Read matrix B
    for (int i = 0; i < N; i++) {
        inf.readToken(row_regex, "B_row");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
