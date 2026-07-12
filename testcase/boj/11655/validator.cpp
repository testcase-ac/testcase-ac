#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single input string S:
    // - it has length 1 to 100
    // - allowed characters: uppercase A–Z, lowercase a–z, digits 0–9, and space
    string s = inf.readLine("[A-Za-z0-9\\ ]{1,100}", "S");
    ensuref(s.front() != ' ' && s.back() != ' ',
            "S must not have leading or trailing spaces");

    // No extra data after the single line
    inf.readEof();
    return 0;
}
