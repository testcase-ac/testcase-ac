#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 50, "T");
    inf.readEoln();

    // Validate each test case
    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Number of cards
        int N = inf.readInt(1, 1000, "N");
        inf.readEoln();

        // Card values
        vector<int> cards = inf.readInts(N, 1, 10000, "a_i");
        inf.readEoln();
    }

    // No extra content
    inf.readEof();
    return 0;
}
