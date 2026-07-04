#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int c = inf.readInt(1, 10, "C");
    inf.readEoln();

    for (int tc = 1; tc <= c; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 10, "N");
        inf.readEoln();

        for (int i = 1; i <= n; ++i) {
            inf.readInt(1, 1000000, "H");
            inf.readSpace();
            inf.readInt(1, 1000000, "W");
            inf.readSpace();
            inf.readLine("BIRD|NOT\\ BIRD", "X");
        }

        int m = inf.readInt(1, 10, "M");
        inf.readEoln();

        for (int i = 1; i <= m; ++i) {
            inf.readInt(1, 1000000, "H");
            inf.readSpace();
            inf.readInt(1, 1000000, "W");
            inf.readEoln();
        }
    }

    inf.readEof();
}
