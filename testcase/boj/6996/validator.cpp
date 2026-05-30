#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 99, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        // CHECK: The Korean statement says length <= 100, while the original
        // English statement says each word contains less than 100 characters.
        inf.readToken("[a-z]{1,99}", "A");
        inf.readSpace();
        inf.readToken("[a-z]{1,99}", "B");
        inf.readEoln();
    }

    // No extra characters after the last newline
    inf.readEof();
    return 0;
}
