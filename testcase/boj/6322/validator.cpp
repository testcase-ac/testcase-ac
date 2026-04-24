#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    
    int test_count = 0;
    const int MAX_TESTS = 100000;
    while (true) {
        // Read three integers: allow values in [-1,10000] so we can catch terminator (0,0,0) and -1s
        int a = inf.readInt(-1, 10000, "a");
        inf.readSpace();
        int b = inf.readInt(-1, 10000, "b");
        inf.readSpace();
        int c = inf.readInt(-1, 10000, "c");
        inf.readEoln();
        
        // Check for terminating line
        if (a == 0 && b == 0 && c == 0) {
            break;
        }
        
        // Count test cases and enforce limit
        test_count++;
        ensuref(test_count <= MAX_TESTS,
                "Number of test cases exceeds the maximum of %d (found at least %d)",
                MAX_TESTS, test_count);
        
        // Exactly one side must be unknown (-1)
        int negs = (a == -1) + (b == -1) + (c == -1);
        ensuref(negs == 1,
                "Test case %d: exactly one side must be -1, but got a=%d, b=%d, c=%d",
                test_count, a, b, c);
        
        // The other two sides must be natural numbers in [1,10000]
        if (a != -1) {
            ensuref(a >= 1 && a <= 10000,
                    "Test case %d: side a must be between 1 and 10000 when not -1 (got %d)",
                    test_count, a);
        }
        if (b != -1) {
            ensuref(b >= 1 && b <= 10000,
                    "Test case %d: side b must be between 1 and 10000 when not -1 (got %d)",
                    test_count, b);
        }
        if (c != -1) {
            ensuref(c >= 1 && c <= 10000,
                    "Test case %d: side c must be between 1 and 10000 when not -1 (got %d)",
                    test_count, c);
        }
        
        // Ensure no zeros except in the terminating line
        ensuref(a != 0 && b != 0 && c != 0,
                "Test case %d: zero is not allowed except in terminating line (got a=%d, b=%d, c=%d)",
                test_count, a, b, c);
    }
    
    // After the terminating "0 0 0" line, file must end immediately
    inf.readEof();
    return 0;
}
