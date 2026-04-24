#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the only line: T, A, B
    int T = inf.readInt(1, 5000000, "T");
    inf.readSpace();
    int A = inf.readInt(1, T, "A");
    inf.readSpace();
    int B = inf.readInt(1, T, "B");
    inf.readEoln();

    // End of file
    inf.readEof();
    return 0;
}
