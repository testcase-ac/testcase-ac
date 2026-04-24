#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the chosen word: lowercase letters, length between 3 and 50.
    inf.readToken("[a-z]{3,50}", "s");
    inf.readEoln();

    // No more input allowed.
    inf.readEof();

    return 0;
}
