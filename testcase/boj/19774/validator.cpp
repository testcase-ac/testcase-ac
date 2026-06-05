#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10000, "t");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);

        string code = inf.readToken("[0-9]{4,4}", "code");
        ensuref((int)code.size() == 4, "code %d length is %d, expected 4", i, (int)code.size());
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
