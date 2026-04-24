#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of people N
    int N = inf.readInt(2, 50, "N");
    inf.readEoln();

    // For each person, read weight x and height y
    for (int i = 1; i <= N; i++) {
        int x = inf.readInt(10, 200, "x_i");
        inf.readSpace();
        int y = inf.readInt(10, 200, "y_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
