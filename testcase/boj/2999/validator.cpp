#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the encrypted message: must be 1 to 100 lowercase letters
    inf.readToken("[a-z]{1,100}", "s");
    inf.readEoln();
    inf.readEof();

    return 0;
}
