#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // To detect duplicate test cases
    set<int> seen;

    for (int i = 0; i < T; i++) {
        // Read start column (A-H)
        string col1 = inf.readToken("[A-H]", "col1");
        inf.readSpace();
        // Read start row (1-8)
        string row1 = inf.readToken("[1-8]", "row1");
        inf.readSpace();
        // Read end column (A-H)
        string col2 = inf.readToken("[A-H]", "col2");
        inf.readSpace();
        // Read end row (1-8)
        string row2 = inf.readToken("[1-8]", "row2");
        // Exactly one newline at end of each test case
        inf.readEoln();

        // Encode the test case uniquely: 6 bits for start, 6 bits for end
        int v1 = (col1[0] - 'A') * 8 + (row1[0] - '1');
        int v2 = (col2[0] - 'A') * 8 + (row2[0] - '1');
        int key = v1 * 64 + v2;

        // Ensure no duplicate test cases
        ensuref(!seen.count(key),
                "Duplicate test case at index %d: %s %s %s %s",
                i, col1.c_str(), row1.c_str(), col2.c_str(), row2.c_str());
        seen.insert(key);
    }

    // No extra characters after the last test case
    inf.readEof();
    return 0;
}
