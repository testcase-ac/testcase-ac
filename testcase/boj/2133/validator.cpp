#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: the width of the 3xN wall
    inf.readInt(1, 30, "N");
    inf.readEoln();

    inf.readEof();
    return 0;
}
