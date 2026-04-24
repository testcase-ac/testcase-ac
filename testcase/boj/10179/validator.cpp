#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases, assume up to 100k if not specified
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // Each price must be in the format digits '.' two digits
    // i.e., one or more digits, a '.', then exactly two digits.
    // No sign, no extra spaces.
    for (int i = 0; i < T; i++) {
        inf.readLine("[0-9]+\\.[0-9]{2}", "price");
    }

    inf.readEof();
    return 0;
}
