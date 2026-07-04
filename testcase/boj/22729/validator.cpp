#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement does not bound the dataset count, so cap both count
    // and total grid area to keep generated inputs practical.
    int t = inf.readInt(1, 100000, "t");
    inf.readEoln();

    int totalArea = 0;
    for (int caseId = 1; caseId <= t; ++caseId) {
        setTestCase(caseId);

        int h = inf.readInt(1, 50, "h");
        inf.readSpace();
        int w = inf.readInt(1, 50, "w");
        inf.readEoln();

        totalArea += h * w;
        ensuref(totalArea <= 2500, "total grid area exceeds practical cap: %d", totalArea);

        set<char> materials;
        for (int row = 1; row <= h; ++row) {
            string line = inf.readToken("[A-Z.]{1,50}", "analysis_row");
            ensuref((int)line.size() == w,
                    "row %d has length %d, expected %d", row, (int)line.size(), w);
            inf.readEoln();

            for (char c : line) {
                if (c != '.') {
                    materials.insert(c);
                }
            }
        }

        ensuref((int)materials.size() <= 7,
                "dataset has %d material kinds, expected at most 7",
                (int)materials.size());
    }

    inf.readEof();
}
