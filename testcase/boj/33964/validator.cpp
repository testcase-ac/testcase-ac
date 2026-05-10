#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read X and Y, each between 1 and 9
    int X = inf.readInt(1, 9, "X");
    inf.readSpace();
    int Y = inf.readInt(1, 9, "Y");
    inf.readEoln();

    // End of file
    inf.readEof();
    return 0;
}
