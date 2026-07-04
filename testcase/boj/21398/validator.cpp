#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 30, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);
        string s = inf.readToken("[A-Z]{1,150}", "s");
        inf.readEoln();
    }

    inf.readEof();
}
