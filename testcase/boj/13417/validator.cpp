#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T (1 ≤ T ≤ 100000)
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        // Read N (1 ≤ N ≤ 1000)
        int N = inf.readInt(1, 1000, "N");
        inf.readEoln();

        // Read N uppercase letters, separated by single spaces
        for (int i = 0; i < N; ++i) {
            // Each card is a single uppercase letter A–Z
            string name = string("card_") + to_string(i);
            inf.readToken("[A-Z]", name.c_str());
            if (i + 1 < N) {
                // Exactly one space between cards
                inf.readSpace();
            }
        }
        // End of this test case's card line
        inf.readEoln();
    }

    // No extra data after all test cases
    inf.readEof();
    return 0;
}
