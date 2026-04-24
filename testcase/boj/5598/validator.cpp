#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the Caesar-encoded word: must be 1 to 1000 uppercase letters, no spaces.
    inf.readToken("[A-Z]{1,1000}", "s");
    inf.readEoln();
    inf.readEof();
    return 0;
}
