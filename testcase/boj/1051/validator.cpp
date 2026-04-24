#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions N and M
    int N = inf.readInt(1, 50, "N");
    inf.readSpace();
    int M = inf.readInt(1, 50, "M");
    inf.readEoln();

    // Read each of the N rows, each should be exactly M digits
    for (int i = 0; i < N; i++) {
        // Read a token consisting of 1 to 50 digits, then check actual length == M
        string row = inf.readToken("[0-9]{1,50}", "row");
        ensuref((int)row.size() == M,
                "Row %d has length %d but expected %d", i+1, (int)row.size(), M);
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
