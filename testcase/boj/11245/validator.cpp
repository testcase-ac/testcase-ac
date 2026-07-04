#include "testlib.h"

#include <string>

using namespace std;

// Validates the stated BOJ 11245 input format: fixed 26-note happiness tables
// followed by bounded start-note and song-length queries.
int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < 26; ++j) {
                inf.readInt(0, 100, "s_ij");
                if (j + 1 < 26) {
                    inf.readSpace();
                } else {
                    inf.readEoln();
                }
            }
        }

        int n = inf.readInt(1, 10, "N");
        inf.readEoln();

        for (int i = 0; i < n; ++i) {
            inf.readToken("[A-Z]", "C");
            inf.readSpace();
            inf.readInt(1, 100000, "L");
            inf.readEoln();
        }
    }

    inf.readEof();
}
