#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the binary string line: only '0' or '1', length between 1 and 100.
    string s = inf.readLine("[01]{1,100}", "binary_string");
    // The first character must be '1'
    ensuref(s[0] == '1', "The first bit must be '1', but found '%c'", s[0]);

    // No more input
    inf.readEof();
    return 0;
}
