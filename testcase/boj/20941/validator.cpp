#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 20, "N");
    inf.readEoln();

    string p1 = inf.readToken("[01]{1,20}", "p_1");
    ensuref(static_cast<int>(p1.size()) == n,
            "p_1 length must be N: expected %d, got %d", n,
            static_cast<int>(p1.size()));
    inf.readEoln();

    inf.readEof();
}
