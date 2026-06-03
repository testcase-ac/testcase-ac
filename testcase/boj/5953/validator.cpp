#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(-1000, 1000, "P_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
