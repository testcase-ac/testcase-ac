#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T
    int T = inf.readInt(1, 20, "T");
    inf.readEoln();

    // For each test case, read one 4-digit number (1000-9999), not all digits identical
    for (int i = 0; i < T; i++) {
        int x = inf.readInt(1000, 9999, "number");
        inf.readEoln();

        // Reject numbers like 1111, 2222, ..., 9999
        // Such numbers are exactly multiples of 1111 in this range
        ensuref(x % 1111 != 0,
                "Number with identical digits at test case %d: %d", 
                i+1, x);
    }

    inf.readEof();
    return 0;
}
