#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read string S: must be 1 to 50 lowercase letters
    inf.readToken("[a-z]{1,50}", "S");
    inf.readEoln();
    inf.readEof();

    return 0;
}
