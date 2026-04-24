#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read the blocks string
    // It must consist solely of characters 'B', 'O', 'J' and have length exactly N.
    string s = inf.readToken("[BOJ]{1,1000}", "blocks");
    ensuref((int)s.size() == N,
            "Length of blocks string (%d) does not match N (%d)",
            (int)s.size(), N);
    inf.readEoln();

    // Validate that the first block is 'B'
    ensuref(s[0] == 'B',
            "First block must be 'B', found '%c'",
            s[0]);

    // No extra content
    inf.readEof();
    return 0;
}
