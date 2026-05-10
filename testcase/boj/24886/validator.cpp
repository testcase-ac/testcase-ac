#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first line: N, p, q, r
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int p = inf.readInt(0, 100000, "p");
    inf.readSpace();
    int q = inf.readInt(0, 100000, "q");
    inf.readSpace();
    int r = inf.readInt(0, 100000, "r");
    inf.readEoln();

    // Check sum constraint
    ensuref(p + q + r <= 100000, "p + q + r = %d + %d + %d = %d > 100000", p, q, r, p+q+r);

    // Read second line: string T of length N, only 'S', 'K', 'H'
    string T = inf.readToken("[SKH]{1,100000}", "T");
    ensuref((int)T.size() == N, "Length of T (%d) does not match N (%d)", (int)T.size(), N);
    inf.readEoln();

    inf.readEof();
}
