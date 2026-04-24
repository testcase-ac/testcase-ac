#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, the value to be partitioned into powers of two
    inf.readInt(1, 1000000, "N");
    inf.readEoln();
    inf.readEof();

    return 0;
}
