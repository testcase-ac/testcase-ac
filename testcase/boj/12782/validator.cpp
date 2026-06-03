#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 50, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        string n = inf.readToken("[01]{1,1000000}", "N");
        inf.readSpace();
        string m = inf.readToken("[01]{1,1000000}", "M");
        inf.readEoln();

        ensuref(n.size() == m.size(), "N and M lengths differ: %d vs %d",
                int(n.size()), int(m.size()));
    }

    inf.readEof();
}
