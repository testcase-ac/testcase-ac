#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(3LL, 1000000000000000000LL, "N");
    inf.readEoln();
    inf.readEof();

    return 0;
}
