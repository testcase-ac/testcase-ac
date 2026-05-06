#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read a single word consisting of only English letters, length between 1 and 100.
    inf.readToken("[a-zA-Z]{1,100}", "word");
    inf.readEoln();
    inf.readEof();

    return 0;
}
