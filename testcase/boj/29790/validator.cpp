#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 130000, "N");
    inf.readSpace();
    inf.readInt(1, 12500, "U");
    inf.readSpace();
    inf.readInt(1, 300, "L");
    inf.readEoln();

    inf.readEof();
    return 0;
}
