#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the first line: H
    // It must be a non-empty string of uppercase letters, no spaces.
    string H = inf.readToken("[A-Z]+", "H");
    inf.readEoln();
    // Check length constraint for H: 1 <= |H| <= 100000
    ensuref((int)H.size() >= 1 && (int)H.size() <= 100000,
            "Length of H must be between 1 and 100000, but found %d", (int)H.size());

    // Read the second line: N
    // It must be a non-empty string of uppercase letters, no spaces.
    string N = inf.readToken("[A-Z]+", "N");
    inf.readEoln();
    // Check length constraint for N: 1 <= |N| <= 10
    ensuref((int)N.size() >= 1 && (int)N.size() <= 10,
            "Length of N must be between 1 and 10, but found %d", (int)N.size());

    // No more input
    inf.readEof();
    return 0;
}
