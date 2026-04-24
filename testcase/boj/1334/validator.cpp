#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single positive integer N with no leading zeros and up to 50 digits
    inf.readToken("[1-9][0-9]{0,49}", "N");
    inf.readEoln();
    inf.readEof();

    return 0;
}
