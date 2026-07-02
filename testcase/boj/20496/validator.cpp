#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 11, "N");
    inf.readEoln();

    int sinkCount = 0;
    string rowPattern = "[S.@]{" + to_string(n) + "}";
    for (int r = 1; r <= n; ++r) {
        string row = inf.readLine(rowPattern, "A_r");
        for (char cell : row) {
            if (cell == 'S') {
                ++sinkCount;
            }
        }
    }

    ensuref(sinkCount == 1, "expected exactly one S, found %d", sinkCount);
    inf.readEof();
}
