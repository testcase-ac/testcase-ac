#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        string expected = inf.readToken("[a-zA-Z]{1,100000}", "I");
        inf.readEoln();

        string produced = inf.readToken("[a-zA-Z]{1,100000}", "P");
        inf.readEoln();
    }

    inf.readEof();
}
