#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read H and G
    int H = inf.readInt(1, 1000, "H");
    inf.readSpace();
    int G = inf.readInt(1, 1000, "G");
    inf.readEoln();

    // Read H Holsteins' coordinates
    for (int i = 1; i <= H; i++) {
        int x = inf.readInt(0, 1000, "holstein_x_" + to_string(i));
        inf.readSpace();
        int y = inf.readInt(0, 1000, "holstein_y_" + to_string(i));
        inf.readEoln();
    }

    // Read G Guernseys' coordinates
    for (int i = 1; i <= G; i++) {
        int x = inf.readInt(0, 1000, "guernsey_x_" + to_string(i));
        inf.readSpace();
        int y = inf.readInt(0, 1000, "guernsey_y_" + to_string(i));
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
