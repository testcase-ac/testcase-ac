#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 1000000, "X");
    inf.readSpace();
    inf.readInt(1, 1000000, "Y");
    inf.readSpace();
    inf.readInt(1, 1000000000, "K");
    inf.readEoln();
    inf.readEof();
    return 0;
}
