#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the first string: must be 1 to 4000 uppercase letters, no spaces
    inf.readLine("[A-Z]{1,4000}", "s1");

    // Read the second string: same constraints
    inf.readLine("[A-Z]{1,4000}", "s2");

    // No extra data after the two lines
    inf.readEof();

    return 0;
}
