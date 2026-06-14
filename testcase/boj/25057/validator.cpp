#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "t");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        string u = inf.readToken("[ABC]{1,200}", "u");
        inf.readEoln();

        string v = inf.readToken("[ABC]{1,200}", "v");
        inf.readEoln();
    }

    inf.readEof();
}
