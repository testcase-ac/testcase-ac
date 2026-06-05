#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    vector<bool> seen(21, false);
    for (int i = 0; i < 20; ++i) {
        int score = inf.readInt(1, 20, "score");
        ensuref(!seen[score], "duplicate score at position %d: %d", i + 1, score);
        seen[score] = true;

        if (i + 1 < 20) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    inf.readEof();
}
