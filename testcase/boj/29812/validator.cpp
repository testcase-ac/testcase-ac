#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 200000, "N");
    inf.readEoln();

    // 2. Read S
    string S = inf.readToken("[A-Za-z]{1,200000}", "S");
    ensuref((int)S.size() == N, "Length of S (%d) does not match N (%d)", (int)S.size(), N);
    inf.readEoln();

    // 3. Read D and M
    int D = inf.readInt(1, 100, "D");
    inf.readSpace();
    int M = inf.readInt(1, 100, "M");
    inf.readEoln();

    // 4. Check S: only alphabets, length == N (already checked by regex and above)
    // No further checks needed for S, as regex ensures only [A-Za-z] and length is checked.

    // 5. No extra lines, check EOF
    inf.readEof();
}
