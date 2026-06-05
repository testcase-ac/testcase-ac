#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int r = inf.readInt(1, 3000, "R");
    inf.readSpace();
    int c = inf.readInt(1, 3000, "C");
    inf.readSpace();
    int h = inf.readInt(1, r, "H");
    inf.readSpace();
    int w = inf.readInt(1, c, "W");
    inf.readEoln();

    ensuref(h % 2 == 1, "H must be odd, got %d", h);
    ensuref(w % 2 == 1, "W must be odd, got %d", w);

    int maxRank = r * c;
    vector<char> seen(maxRank + 1, 0);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            int q = inf.readInt(1, maxRank, "Q_i_j");
            ensuref(!seen[q], "quality rank %d appears more than once", q);
            seen[q] = 1;
        }
        inf.readEoln();
    }

    inf.readEof();
}
