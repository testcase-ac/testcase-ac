#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of songs A and average I
    int A = inf.readInt(1, 100, "A");
    inf.readSpace();
    int I = inf.readInt(1, 100, "I");
    inf.readEoln();

    // No further constraints implied for input
    inf.readEof();
    return 0;
}
