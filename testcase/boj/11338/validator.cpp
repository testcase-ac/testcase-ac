#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 30, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int q = inf.readInt(1, 100000, "Q");
        inf.readSpace();
        int k = inf.readInt(1, 100000, "K");
        inf.readEoln();

        for (int i = 1; i <= q; ++i) {
            string op = inf.readToken("insert|print", "instruction");
            if (op == "insert") {
                inf.readSpace();
                inf.readInt(0, 2147483647, "N");
            }
            inf.readEoln();
        }
    }

    inf.readEof();
}
