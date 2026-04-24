#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read triangle vertices
    int xA = inf.readInt(1, 1000, "x_A");
    inf.readSpace();
    int yA = inf.readInt(1, 1000, "y_A");
    inf.readEoln();

    int xB = inf.readInt(1, 1000, "x_B");
    inf.readSpace();
    int yB = inf.readInt(1, 1000, "y_B");
    inf.readEoln();

    int xC = inf.readInt(1, 1000, "x_C");
    inf.readSpace();
    int yC = inf.readInt(1, 1000, "y_C");
    inf.readEoln();

    // Check triangle is non-degenerate: area2 != 0
    // area2 = xA*(yB - yC) + xB*(yC - yA) + xC*(yA - yB)
    long long area2 = (long long)xA * (yB - yC)
                    + (long long)xB * (yC - yA)
                    + (long long)xC * (yA - yB);
    ensuref(area2 != 0,
            "Triangle is degenerate: computed twice-area = 0");

    // Number of trees
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Read each tree coordinate
    for (int i = 0; i < N; i++) {
        int xt = inf.readInt(1, 1000, "tree_x");
        inf.readSpace();
        int yt = inf.readInt(1, 1000, "tree_y");
        inf.readEoln();
    }

    // File must end here
    inf.readEof();
    return 0;
}
