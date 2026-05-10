#include "testlib.h"
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int N = inf.readInt(1, 50, "N");
        inf.readSpace();
        int M = inf.readInt(1, 50, "M");
        inf.readEoln();

        for (int i = 0; i < N; ++i) {
            string row = inf.readToken("[.#?]{1,50}", "row");
            inf.readEoln();

            ensuref((int)row.size() == M,
                    "Row %d in test case %d has length %d, expected %d",
                    i + 1, tc, (int)row.size(), M);
        }
    }

    inf.readEof();
}
