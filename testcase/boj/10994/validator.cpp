#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and validate constraints
    int N = inf.readInt(1, 100, "N");
    // After N there should be exactly one end of line
    inf.readEoln();
    // No extra data
    inf.readEof();

    return 0;
}
