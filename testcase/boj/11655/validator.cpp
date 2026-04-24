#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single input string S:
    // - it may be empty up to length 100
    // - allowed characters: uppercase A–Z, lowercase a–z, digits 0–9, and space
    inf.readLine("[A-Za-z0-9\\ ]{0,100}", "S");

    // No extra data after the single line
    inf.readEof();
    return 0;
}
