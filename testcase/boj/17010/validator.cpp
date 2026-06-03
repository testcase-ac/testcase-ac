#include "testlib.h"
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no upper bound for L; use the local default cap.
    int L = inf.readInt(1, 100000, "L");
    inf.readEoln();

    for (int i = 0; i < L; ++i) {
        int N = inf.readInt(1, 79, "N");
        inf.readSpace();

        char symbol = inf.readChar();
        ensuref(!isspace((unsigned char)symbol),
                "symbol on line %d must be a non-space character", i + 2);
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
