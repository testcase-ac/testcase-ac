#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 20, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 1000000, "N");
        inf.readSpace();
        string b = inf.readToken("[01?]{1,1000000}", "B");
        inf.readEoln();

        ensuref((int)b.size() == n, "B length must equal N, got N=%d and |B|=%d", n, (int)b.size());
    }

    inf.readEof();
}
