#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int dataset = 0;
    while (true) {
        int w = inf.readInt(0, 50, "w");
        inf.readSpace();
        int h = inf.readInt(0, 50, "h");
        inf.readEoln();

        if (w == 0 && h == 0) {
            break;
        }

        ++dataset;
        setTestCase(dataset);
        ensuref(w >= 1, "dataset %d has invalid width %d", dataset, w);
        ensuref(h >= 1, "dataset %d has invalid height %d", dataset, h);

        for (int row = 1; row <= h; ++row) {
            string line = inf.readToken("[BW.]{1,50}", "row");
            inf.readEoln();
            ensuref((int)line.size() == w,
                    "dataset %d row %d has length %d, expected %d",
                    dataset,
                    row,
                    (int)line.size(),
                    w);
        }
    }

    inf.readEof();
    return 0;
}
