#include "testlib.h"
#include <string>
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read dimensions h, w
        int h = inf.readInt(2, 100, "h");
        inf.readSpace();
        int w = inf.readInt(2, 100, "w");
        inf.readEoln();

        // Read the map: h lines, each of length w
        for (int i = 0; i < h; i++) {
            string row = inf.readLine("[^]+", "map_row");
            // Check length
            ensuref((int)row.size() == w,
                    "In test %d, line %d length %d is not equal to w=%d",
                    tc, i+1, (int)row.size(), w);
            // Check each character
            for (int j = 0; j < w; j++) {
                char c = row[j];
                bool ok = false;
                if (c == '.' || c == '*' || c == '$') ok = true;
                else if ('A' <= c && c <= 'Z') ok = true;
                else if ('a' <= c && c <= 'z') ok = true;
                ensuref(ok,
                        "In test %d, map[%d][%d] has invalid character '%c'",
                        tc, i+1, j+1, c);
            }
        }

        // Read initial keys line: either "0" or one or more lowercase letters
        string keys = inf.readToken("[^]+", "keys");
        // keys token must not be empty
        ensuref(!keys.empty(),
                "In test %d, keys string is empty", tc);
        if (keys == "0") {
            // ok: no keys
        } else {
            // must be all lowercase letters
            for (int i = 0; i < (int)keys.size(); i++) {
                char c = keys[i];
                ensuref('a' <= c && c <= 'z',
                        "In test %d, keys[%d] = '%c' is not a lowercase letter or '0'",
                        tc, i+1, c);
            }
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
