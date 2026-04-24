#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the palindrome candidate: only lowercase letters, no spaces
    string w = inf.readToken("[a-z]+", "w");
    int n = (int)w.size();
    // Check length constraint: 5 ≤ n ≤ 100000
    ensuref(n >= 5 && n <= 100000,
            "Length of string w must be between 5 and 100000, found %d", n);

    // Exactly one newline after the string, then EOF
    inf.readEoln();
    inf.readEof();

    return 0;
}
