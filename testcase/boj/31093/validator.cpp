#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 500000, "N");
    inf.readSpace();
    int k = inf.readInt(2, 500000, "K");
    inf.readEoln();

    ensuref(n % 2 == 0, "N must be even, got %d", n);

    string s = inf.readToken("[23E]{1,500000}", "S");
    inf.readEoln();

    ensuref((int)s.size() == n, "S length must be N, got %d for N=%d",
            (int)s.size(), n);

    inf.readEof();
}
