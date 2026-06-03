#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int type = inf.readInt(1, 3, "type");
        if (type == 1 || type == 2) {
            inf.readSpace();
            string c = inf.readToken("[A-Za-z]", "c");
            ensuref(c.size() == 1, "c must be one alphabetic character at operation %d", i);
        }
        inf.readEoln();
    }

    inf.readEof();
}
