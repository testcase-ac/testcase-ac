#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        string ends = inf.readToken("[INU]{2}", "ends");
        inf.readSpace();
        inf.readInt(1, 1000, "t_i");
        inf.readEoln();
    }

    inf.readEof();
}
