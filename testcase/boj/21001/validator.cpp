#include "testlib.h"

#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int z = inf.readInt(1, 100000, "z");
    inf.readEoln();

    long long totalLength = 0;
    for (int tc = 1; tc <= z; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 25000, "n");
        inf.readSpace();
        string required = inf.readToken("[a-z]", "K");
        inf.readEoln();

        string s = inf.readToken("[a-z]{1,25000}", "s");
        inf.readEoln();
        string t = inf.readToken("[a-z]{1,25000}", "t");
        inf.readEoln();

        ensuref((int)s.size() == n, "s length is %d instead of n=%d", (int)s.size(), n);
        ensuref((int)t.size() == n, "t length is %d instead of n=%d", (int)t.size(), n);
        ensuref(s < t, "s must be lexicographically earlier than t");

        totalLength += n;
        ensuref(totalLength <= 100000, "sum of n exceeds 100000");
    }

    inf.readEof();
}
