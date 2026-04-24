#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int64_t tc = 0;
    while (true) {
        // Read one line: must be 1 to 5 digits, no spaces or other chars
        string s = inf.readLine("[0-9]{1,5}", "factorial_number");
        tc++;
        // If this line is the sentinel "0", stop reading further test cases
        if (s == "0") {
            break;
        }
        // Otherwise it's a real test case; nothing more to check per-case
    }

    // The sentinel "0" line is not counted as a test case for the limit
    int64_t real_tests = tc - 1;
    ensuref(real_tests <= 100000,
            "Number of test cases %d exceeds the maximum of 100000", 
            real_tests);

    inf.readEof();
    return 0;
}
