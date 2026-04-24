#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the string S: must be 1 to 1,000,000 lowercase letters
    inf.readToken("[a-z]{1,1000000}", "S");
    // There must be exactly one newline after S
    inf.readEoln();
    // No extra content after the single test case
    inf.readEof();

    return 0;
}
