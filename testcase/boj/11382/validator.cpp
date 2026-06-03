#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(1LL, 1000000000000LL, "A");
    inf.readSpace();
    inf.readLong(1LL, 1000000000000LL, "B");
    inf.readSpace();
    inf.readLong(1LL, 1000000000000LL, "C");
    inf.readEoln();

    inf.readEof();
    return 0;
}
