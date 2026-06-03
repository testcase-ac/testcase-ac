#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    vector<bool> seen(101, false);
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            int round = inf.readInt(1, 100, "round");
            ensuref(!seen[round], "duplicate shot round %d at row %d column %d",
                    round, i + 1, j + 1);
            seen[round] = true;

            if (j + 1 < 10) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
}
