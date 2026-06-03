#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);
        inf.readToken("[A-Z]{1,100}", "word");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
