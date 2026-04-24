#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read block dimensions
    int width = inf.readInt(1, 100, "width");
    inf.readSpace();
    int height = inf.readInt(1, 100, "height");
    inf.readEoln();

    // Number of stores
    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    // Read each store
    for (int i = 0; i < n; i++) {
        int d = inf.readInt(1, 4, "d");
        inf.readSpace();
        if (d == 1 || d == 2) {
            // North or South: position along width, cannot be at corners
            inf.readInt(1, width - 1, "l");
        } else {
            // West or East: position along height, cannot be at corners
            inf.readInt(1, height - 1, "l");
        }
        inf.readEoln();
    }

    // Read guard's position
    int gd = inf.readInt(1, 4, "d");
    inf.readSpace();
    if (gd == 1 || gd == 2) {
        inf.readInt(1, width - 1, "l");
    } else {
        inf.readInt(1, height - 1, "l");
    }
    inf.readEoln();

    // End of file
    inf.readEof();
    return 0;
}
