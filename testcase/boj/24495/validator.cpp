#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        for (int i = 0; i < 8; ++i) {
            if (i > 0) {
                inf.readSpace();
            }
            inf.readInt(1, 10, "face");
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
