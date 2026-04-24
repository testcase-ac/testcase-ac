#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(1, 1000000, "n");
    inf.readEoln();

    // Read string S: must consist of lowercase letters only, length exactly n
    string s = inf.readLine("[a-z]+", "S");
    ensuref((int)s.size() == n,
            "Length of S (%d) does not match n (%d)", (int)s.size(), n);

    // No extra lines, end of file immediately
    inf.readEof();
    return 0;
}
