#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first string: only uppercase letters, length 1 to 1000
    inf.readToken("[A-Z]{1,1000}", "s1");
    inf.readEoln();

    // Read second string: only uppercase letters, length 1 to 1000
    inf.readToken("[A-Z]{1,1000}", "s2");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
