#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 250, "N");
    inf.readEoln();

    for (int row = 1; row <= n; ++row) {
        inf.readToken(format("[01]{%d}", n), format("row[%d]", row).c_str());
        inf.readEoln();
    }

    inf.readEof();
}
