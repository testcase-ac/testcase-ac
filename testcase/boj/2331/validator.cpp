#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read A and P according to problem constraints
    int A = inf.readInt(1, 9999, "A");
    inf.readSpace();
    int P = inf.readInt(1, 5, "P");
    inf.readEoln();

    // No further lines expected
    inf.readEof();
    return 0;
}
