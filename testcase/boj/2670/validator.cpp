#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 10000, "N");
    inf.readEoln();

    // Read N positive real numbers with exactly one decimal place
    for (int i = 0; i < N; i++) {
        // Must match a single digit, dot, single digit (0.0 to 9.9)
        string s = inf.readToken("[0-9]\\.[0-9]", "a_i");
        // Parse to ensure numeric bounds explicitly
        int x = (s[0] - '0') * 10 + (s[2] - '0');  // value in tenths
        ensuref(0 <= x && x <= 99, "Value out of range at index %d: %s", i+1, s.c_str());
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
