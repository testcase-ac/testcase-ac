#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    inf.readInt(1, 1000000000, "K");
    inf.readEoln();

    string s = inf.readToken("[a-z]{1,100000}", "S");
    ensuref((int)s.size() == n, "S length must be N: length=%d N=%d", (int)s.size(), n);
    inf.readEoln();

    vector<int> seen(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        int a = inf.readInt(1, n, "A_i");
        ensuref(!seen[a], "A_i must be distinct: duplicate value %d at index %d", a, i);
        seen[a] = 1;

        if (i == n) {
            inf.readEoln();
        } else {
            inf.readSpace();
        }
    }

    inf.readEof();
}
