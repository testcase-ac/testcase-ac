#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 13, "N");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        setTestCase(i);
        string s = inf.readToken("[ABC]{2,13}", "S_i");
        ensuref((int)s.size() == n, "S_%d length is %d, expected %d", i, (int)s.size(), n);
        inf.readEoln();
    }

    inf.readEof();
}
