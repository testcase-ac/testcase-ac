#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 1000, "N");
    inf.readEoln();

    inf.readInt(1, 1000, "A");
    inf.readSpace();
    inf.readInt(1, 1000, "B");
    inf.readEoln();

    inf.readEof();
    return 0;
}
