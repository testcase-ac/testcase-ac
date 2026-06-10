#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long MAX_VALUE = 1000000000000000000LL;

    inf.readLong(0LL, MAX_VALUE, "x_0");
    inf.readSpace();
    inf.readLong(0LL, MAX_VALUE, "N");
    inf.readEoln();

    inf.readEof();
    return 0;
}
