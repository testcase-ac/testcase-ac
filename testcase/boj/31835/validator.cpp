#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1999, "N");
    inf.readEoln();
    ensuref(n % 2 == 1, "N must be odd: %d", n);

    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }

        if (i % 2 == 1) {
            inf.readToken("[TF]", "A_i");
        } else {
            string op = inf.readToken("[^ ]{1,1}", "A_i");
            ensuref(op == "&" || op == "|", "operator A_%d must be & or |: %s", i, op.c_str());
        }
    }
    inf.readEoln();

    inf.readToken("[TF]", "C");
    inf.readEoln();

    inf.readEof();
    return 0;
}
