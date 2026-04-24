#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single uppercase word s (length 1..20, only 'A' to 'Z')
    string s = inf.readToken("[A-Z]{1,20}", "s");
    // Ensure exactly one newline after the token
    inf.readEoln();

    // Count occurrences of 'S' and enforce at most 3
    int cntS = 0;
    for (char c : s) {
        if (c == 'S') ++cntS;
    }
    ensuref(cntS <= 3,
            "The letter 'S' occurs %d times, but at most 3 occurrences are allowed", 
            cntS);

    // No extra content after the single test case
    inf.readEof();

    return 0;
}
