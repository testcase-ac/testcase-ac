#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100000, "N");
        inf.readEoln();

        string p = inf.readToken("[URYBOPGA]{1,100000}", "P");
        ensuref((int)p.size() == n, "P length must equal N: N=%d, length=%d", n, (int)p.size());
        inf.readEoln();
    }

    inf.readEof();
}
