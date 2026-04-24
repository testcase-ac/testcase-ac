#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: the required kilograms of sugar
    int N = inf.readInt(3, 5000, "N");
    inf.readEoln();  // end of the single line

    inf.readEof();   // no extra characters
    return 0;
}
