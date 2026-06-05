#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "N");
    inf.readEoln();

    for (int tc = 1; tc <= n; ++tc) {
        setTestCase(tc);

        int x = inf.readInt(1, 3, "X");
        inf.readEoln();

        for (int i = 0; i <= x; ++i) {
            inf.readToken("[1-9]|!", "operand");
            if (i < x) {
                inf.readSpace();
                inf.readToken("[+]", "operator");
                inf.readSpace();
            }
        }
        inf.readEoln();
    }

    inf.readEof();
}
