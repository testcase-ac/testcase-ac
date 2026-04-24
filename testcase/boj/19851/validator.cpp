#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    // Read the parentheses string of length N
    string s = inf.readToken("[()]+", "s");
    ensuref((int)s.size() == N,
            "Length of string s (%d) does not match N (%d)", (int)s.size(), N);
    inf.readEoln();

    // Read Q
    int Q = inf.readInt(1, 300000, "Q");
    inf.readEoln();

    // Read Q queries
    for (int i = 1; i <= Q; i++) {
        int t = inf.readInt(1, 2, "t_i");
        inf.readSpace();
        int a = inf.readInt(1, N, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, N, "b_i");
        inf.readEoln();

        ensuref(a <= b,
                "In query %d: a_i (%d) must be <= b_i (%d)", i, a, b);
        // t is already in [1,2], no further check needed
    }

    inf.readEof();
    return 0;
}
