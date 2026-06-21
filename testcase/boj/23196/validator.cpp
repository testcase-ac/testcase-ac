#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "n");
    inf.readSpace();
    int k = inf.readInt(0, 200000, "k");
    inf.readEoln();

    for (int i = 1; i <= k; ++i) {
        string c = inf.readToken("[RDHV]", "c");
        inf.readSpace();
        int x1 = inf.readInt(1, n, "x_1");
        inf.readSpace();
        int x2 = inf.readInt(x1, n, "x_2");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
