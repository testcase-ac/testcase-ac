#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of gates
    int G = inf.readInt(1, 100000, "G");
    inf.readEoln();

    // Number of planes
    int P = inf.readInt(1, 100000, "P");
    inf.readEoln();

    // Each plane's maximum dockable gate
    for (int i = 0; i < P; i++) {
        inf.readInt(1, G, "g_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
