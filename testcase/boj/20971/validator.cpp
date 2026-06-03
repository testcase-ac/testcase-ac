#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    string colors = inf.readToken("[A-Z]{1,100000}", "colors");
    ensuref((int)colors.size() == n, "colors length must be N: got %d, expected %d",
            (int)colors.size(), n);
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(a, n, "b");
        inf.readEoln();
    }

    inf.readEof();
}
