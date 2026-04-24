#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = 0;
    long long sumLen = 0;

    // Read test cases until a single dot "." line
    while (true) {
        // Read an entire non-empty line (could be the "." terminator or a string s)
        string line = inf.readLine("[^]+", "line");

        // Check for the terminator
        if (line == ".") {
            break;
        }

        // It's a real test case
        t++;
        ensuref(t <= 10, "Number of test cases exceeds 10 (found %d)", t);

        // Check length constraint for s
        long long len = (long long)line.length();
        ensuref(len >= 1 && len <= 1000000,
                "Length of string at test case %d is out of range: %lld", t, len);

        // Accumulate total length (implicit sum ≤ 10*1e6)
        sumLen += len;
        ensuref(sumLen <= 10000000,
                "Total length of all strings exceeds 10000000 (is %lld)", sumLen);

        // Check that s contains only lowercase letters
        for (int i = 0; i < (int)line.size(); i++) {
            char c = line[i];
            ensuref(c >= 'a' && c <= 'z',
                    "Invalid character in string at test case %d, position %d: '%c'",
                    t, i+1, c);
        }
    }

    // Must have at least one test case
    ensuref(t >= 1, "No test cases found");

    inf.readEof();
    return 0;
}
