#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the string S: must consist of lowercase letters only
    string S = inf.readToken("[a-z]+", "S");
    // Check length constraint: 1 <= |S| <= 100000
    ensuref((int)S.size() >= 1 && (int)S.size() <= 100000,
            "Length of S must be between 1 and 100000, found %d", (int)S.size());
    // End of line after S
    inf.readEoln();
    // No extra input
    inf.readEof();

    return 0;
}
