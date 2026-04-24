#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    // Number of test cases
    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();
    // Each of the next n lines: a 24-bit binary string representing a positive number
    for (int i = 1; i <= n; i++) {
        // Read entire line and ensure exactly 24 characters of '0' or '1'
        string s = inf.readLine("[01]{24}", "binary_string");
        // Ensure the number is positive (at least one '1')
        ensuref(s.find('1') != string::npos,
                "Binary string at test case %d has no '1' bits (must represent a positive number)", i);
    }
    inf.readEof();
    return 0;
}
