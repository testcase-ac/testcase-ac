#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // For each test case
    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // k: number of words
        int k = inf.readInt(1, 100, "k");
        inf.readEoln();

        // Sum of lengths in this test case
        long long sumLen = 0;
        for (int i = 1; i <= k; i++) {
            // Each word: non-empty, lowercase letters only
            // Maximum single word length <=10000 (enforced by sum check below)
            string name = "word_" + to_string(i);
            string s = inf.readToken("[a-z]+", name.c_str());
            inf.readEoln();

            sumLen += (int)s.length();
            ensuref(sumLen <= 10000,
                    "Total length of words in test case %d exceeds limit: %lld > 10000",
                    tc, sumLen);
        }
    }

    // No extra characters
    inf.readEof();
    return 0;
}
