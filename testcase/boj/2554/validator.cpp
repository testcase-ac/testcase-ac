#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: a natural number with up to 100 digits, no leading zeros.
    // We assume natural numbers start from 1.
    inf.readToken("[1-9][0-9]{0,99}", "N");
    inf.readEoln();

    inf.readEof();
    return 0;
}
