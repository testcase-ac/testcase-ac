#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the whole input line as the string S
    string s = inf.readLine("[A-Z]{1,500000}", "s");
    // The regex already ensures:
    // - length in [1, 500000]
    // - only uppercase A-Z
    // - no spaces or other characters

    // No extra tokens or lines allowed
    inf.readEof();
}
