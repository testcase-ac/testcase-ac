#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(1LL, 1000000000000LL, "x");
    inf.readEoln();
    inf.readEof();
    return 0;
}
