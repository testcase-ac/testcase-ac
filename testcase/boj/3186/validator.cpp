#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read K, L, N
    int K = inf.readInt(1, 1000, "K");
    inf.readSpace();
    int L = inf.readInt(1, 1000, "L");
    inf.readSpace();
    int N = inf.readInt(1, 10000, "N");
    inf.readEoln();

    // Read the sequence of length N consisting only of '0' and '1'
    string s = inf.readToken("[01]{1,10000}", "s");
    ensuref((int)s.size() == N,
            "Length of sequence s (%d) does not equal N (%d)", (int)s.size(), N);
    inf.readEoln();

    // No other global constraints to check
    inf.readEof();
    return 0;
}
