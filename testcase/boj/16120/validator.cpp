#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the PPAP candidate string: only 'P' and 'A' characters
    string s = inf.readToken("[PA]+", "s");
    // Validate length constraints
    ensuref((int)s.size() >= 1 && (int)s.size() <= 1000000,
            "Length of s is %d, but must be between 1 and 1000000", (int)s.size());
    // After the string, there must be exactly one end-of-line
    inf.readEoln();
    // No extra content in file
    inf.readEof();

    return 0;
}
