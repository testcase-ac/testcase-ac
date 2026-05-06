#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read X: the position in the zigzag enumeration
    inf.readInt(1, 10000000, "X");
    inf.readEoln();

    // No more data
    inf.readEof();
    return 0;
}
