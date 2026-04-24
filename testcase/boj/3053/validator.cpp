#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read radius R: a natural number (>=1) and <=10000
    int R = inf.readInt(1, 10000, "R");
    inf.readEoln();    // exactly one newline after R
    inf.readEof();     // no extra data

    return 0;
}
