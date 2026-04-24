#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the binary string N: must be 1 to 1000 characters long, only '0' or '1'
    // and cannot be exactly "0"
    string N = inf.readToken("[01]{1,1000}", "N");
    ensuref(!(N.size() == 1 && N[0] == '0'),
            "N must not be \"0\"");

    // End of line after N
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
