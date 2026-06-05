#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(10, 15, "N");
    inf.readEoln();

    string commands = inf.readToken("[FLR]{10,50}", "A");
    inf.readEoln();

    int zombieCount = 0;
    int switchCount = 0;
    for (int i = 0; i < n; ++i) {
        string row = inf.readToken("[OSZ]{" + to_string(n) + "}", "row");
        inf.readEoln();

        for (int j = 0; j < n; ++j) {
            if (row[j] == 'Z') {
                ++zombieCount;
            } else if (row[j] == 'S') {
                ++switchCount;
            }
        }

        if (i == 0) {
            ensuref(row[0] == 'O', "initial cell (1, 1) must be O");
        }
    }

    ensuref(zombieCount <= 2 * n, "too many zombies: %d > %d", zombieCount, 2 * n);
    ensuref(switchCount <= 2 * n, "too many switches: %d > %d", switchCount, 2 * n);

    inf.readEof();
}
