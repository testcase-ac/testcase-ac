#include "testlib.h"
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 200, "n");
        inf.readEoln();

        vector<string> before(n), after(n);

        for (int i = 0; i < n; ++i) {
            before[i] = inf.readToken("[RYB][0-9]", "card_before");
            if (i + 1 < n) inf.readSpace();
        }
        inf.readEoln();

        for (int i = 0; i < n; ++i) {
            after[i] = inf.readToken("[RYB][0-9]", "card_after");
            if (i + 1 < n) inf.readSpace();
        }
        inf.readEoln();
    }

    inf.readEof();
}
