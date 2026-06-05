#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100, "M");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        string s = inf.readToken("[a-z]{1,100}", "s_i");
        ensuref((int)s.size() == m, "s_%d length is %d, expected %d", i, (int)s.size(), m);
        inf.readEoln();
    }

    inf.readEof();
}
