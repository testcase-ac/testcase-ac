#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 8, "start_x");
    inf.readSpace();
    inf.readInt(1, 8, "start_y");
    inf.readEoln();

    inf.readInt(1, 8, "target_x");
    inf.readSpace();
    inf.readInt(1, 8, "target_y");
    inf.readEoln();

    inf.readEof();
    return 0;
}
