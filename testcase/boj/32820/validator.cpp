#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read m and n
    int m = inf.readInt(1, 100000, "m");
    inf.readSpace();
    int n = inf.readInt(1, 200000, "n");
    inf.readEoln();

    // Read P
    string P = inf.readToken("[a-z]{1,200000}", "P");
    ensuref((int)P.size() == m, "Length of P (%d) does not match m (%d)", (int)P.size(), m);
    inf.readEoln();

    // Read T
    string T = inf.readToken("[a-z]{1,200000}", "T");
    ensuref((int)T.size() == n, "Length of T (%d) does not match n (%d)", (int)T.size(), n);
    inf.readEoln();

    inf.readEof();
}
