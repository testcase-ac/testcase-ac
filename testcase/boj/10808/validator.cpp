#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single word S: only lowercase letters, length between 1 and 100.
    inf.readToken("[a-z]{1,100}", "S");
    inf.readEoln();

    // No extra data.
    inf.readEof();
    return 0;
}
