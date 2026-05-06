#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of islands
    int N = inf.readInt(2, 1000, "N");
    inf.readEoln();

    // Coordinates of each island
    for (int i = 0; i < N; i++) {
        int x = inf.readInt(-30000, 30000, "x_i");
        inf.readSpace();
        int y = inf.readInt(-30000, 30000, "y_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
