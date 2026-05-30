#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; i++) {
        if (i > 1) {
            inf.readSpace();
        }

        string s = inf.readToken("mumble|0|[1-9][0-9]{0,4}", "a_i_or_mumble");
        if (s != "mumble") {
            int val = stoi(s);
            ensuref(0 <= val && val <= 10000,
                    "Integer at position %d (%d) out of allowed range [0,10000]",
                    i, val);
        }
    }

    inf.readEoln();
    inf.readEof();

    return 0;
}
