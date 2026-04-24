#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: a natural number (positive integer) up to 20000
    int N = inf.readInt(1, 20000, "N");
    // After N there must be exactly one newline
    inf.readEoln();
    // No extra characters after the newline
    inf.readEof();

    return 0;
}
