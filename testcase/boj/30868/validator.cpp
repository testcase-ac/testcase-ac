#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int i = 1; i <= T; ++i) {
        setTestCase(i);
        inf.readInt(1, 100, "n");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
