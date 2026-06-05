#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 1000000000, "n");
    inf.readSpace();
    inf.readInt(0, 1000000000, "m");
    inf.readEoln();

    inf.readEof();
    return 0;
}
