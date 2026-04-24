#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    // Each test case: a 16‐digit credit card number
    for (int i = 0; i < T; i++) {
        // Read a line of exactly 16 digits (no spaces, no extra chars)
        inf.readLine("[0-9]{16}", "card_number");
    }

    inf.readEof();
    return 0;
}
