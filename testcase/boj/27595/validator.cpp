#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(1, 1000000, "n");
    inf.readEoln();

    // Read the wine-string s
    // It must consist only of 'R' or 'W'
    string s = inf.readToken("[RW]+", "s");
    // Validate its length is exactly 2*n - 1
    int expected_len = 2 * n - 1;
    ensuref((int)s.size() == expected_len,
            "The length of s must be %d, but got %d", expected_len, (int)s.size());
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
