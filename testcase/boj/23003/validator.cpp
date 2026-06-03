#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 200000, "N");
        inf.readEoln();

        string s = inf.readToken("[A-Z]{1,200000}", "S");
        ensuref((int)s.size() == n, "S length must equal N: expected %d, got %d",
                n, (int)s.size());
        inf.readEoln();
    }

    inf.readEof();
}
