#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(2, 100, "N");
    inf.readEoln();

    // Read the grid: N lines, each exactly N alphabetic characters
    for (int i = 0; i < N; i++) {
        // Read a token of up to 100 letters, then check its length
        string row = inf.readToken("[A-Za-z]{1,100}", "row");
        ensuref((int)row.size() == N,
                "row %d length must be exactly N=%d, but got %d", i+1, N, (int)row.size());
        inf.readEoln();
    }

    // Read K
    int K = inf.readInt(1, 3, "K");
    inf.readEoln();

    // No extra data
    inf.readEof();

    return 0;
}
