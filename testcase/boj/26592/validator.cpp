#include "testlib.h"
#include <string>
#include <limits>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of triangles
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    // For each triangle, read area and base length
    // We assume area >= 0 and base > 0. No explicit upper bound given in statement,
    // so we allow values up to 1e300 (within double range).
    const double MAXV = 1e300;
    for (int i = 1; i <= n; i++) {
        // area_i
        string areaName = "area[" + to_string(i) + "]";
        double area = inf.readDouble(0.0, MAXV, areaName.c_str());

        // exactly one space
        inf.readSpace();

        // base_i
        string baseName = "base[" + to_string(i) + "]";
        double base = inf.readDouble(0.0, MAXV, baseName.c_str());
        ensuref(base > 0.0,
                "Base length must be positive at line %d, but got %g", 
                i, base);

        // end of line
        inf.readEoln();
    }

    // no extra content
    inf.readEof();
    return 0;
}
