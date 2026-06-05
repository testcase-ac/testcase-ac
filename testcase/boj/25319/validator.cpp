#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 50, "n");
    inf.readSpace();
    int m = inf.readInt(2, 50, "m");
    inf.readSpace();
    int s_len = inf.readInt(1, 1000, "s_len");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        string row = inf.readToken("[a-z]{1,50}", "row");
        ensuref((int)row.size() == m, "row %d has length %d, expected %d",
                i + 1, (int)row.size(), m);
        inf.readEoln();
    }

    string s = inf.readToken("[a-z]{1,1000}", "s");
    ensuref((int)s.size() == s_len, "s has length %d, expected %d",
            (int)s.size(), s_len);
    inf.readEoln();
    inf.readEof();
}
