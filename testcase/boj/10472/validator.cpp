#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int P = inf.readInt(1, 50, "P");
    inf.readEoln();

    for (int tc = 0; tc < P; ++tc) {
        setTestCase(tc + 1);

        // Read exactly 3 lines of 3 characters: only '*' or '.'
        for (int i = 0; i < 3; ++i) {
            string line = inf.readLine("[*.]{3}", "board_row");
            ensuref((int)line.size() == 3,
                    "Row %d of test %d must have exactly 3 characters, got %d",
                    i + 1, tc + 1, (int)line.size());
        }
    }

    inf.readEof();
}
