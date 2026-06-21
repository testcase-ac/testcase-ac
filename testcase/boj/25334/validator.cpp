#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 1000000, "n");
        inf.readSpace();
        int k = inf.readInt(1, n, "k");
        inf.readEoln();

        string a = inf.readToken("[01]{1,1000000}", "A");
        ensuref(static_cast<int>(a.size()) == n,
                "A length must be n: n=%d, length=%d",
                n,
                static_cast<int>(a.size()));
        inf.readEoln();
    }

    inf.readEof();
}
