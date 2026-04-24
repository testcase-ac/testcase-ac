#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: the natural number to represent
    inf.readInt(1, 10000000, "N");
    inf.readEoln();   // exactly one newline after N
    inf.readEof();    // no extra characters after that

    return 0;
}
