#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int catKinds = 0;
    bool hasWhite = false;
    bool hasBlack = false;
    bool hasGray = false;

    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            string pixel = inf.readToken("[wbgryop]", "pixel");

            if (pixel == "w" && !hasWhite) {
                hasWhite = true;
                ++catKinds;
            } else if (pixel == "b" && !hasBlack) {
                hasBlack = true;
                ++catKinds;
            } else if (pixel == "g" && !hasGray) {
                hasGray = true;
                ++catKinds;
            }

            if (j + 1 < 15) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    ensuref(catKinds == 1, "expected exactly one cat color among w, b, g, found %d", catKinds);
    inf.readEof();
}
