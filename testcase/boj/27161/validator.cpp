#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        string s = inf.readToken("CLOCK|WATCH|HOURGLASS", "S");
        inf.readSpace();
        int x = inf.readInt(1, 12, "X");
        inf.readEoln();

        (void)s;
        (void)x;
    }

    inf.readEof();
}
