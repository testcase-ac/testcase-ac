#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "n");
    inf.readEoln();

    string s = inf.readToken("[+-]{1,200000}", "s");
    ensuref((int)s.size() == n, "s length must be n: expected %d, got %d",
            n, (int)s.size());
    inf.readEoln();

    int q = inf.readInt(1, 100000, "q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        inf.readLong(1LL, 1000000000LL, "a_j");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "b_j");
        inf.readEoln();
    }

    inf.readEof();
}
