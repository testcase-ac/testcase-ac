#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test strings
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // Each string: length 1 to 200, only '{', '}', ','
    for (int i = 1; i <= T; i++) {
        // Read the string as a token (no spaces allowed; must match exactly)
        inf.readToken("[\\{\\},]{1,200}", "s");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
