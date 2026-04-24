#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of vertices of the convex polygon
    int N = inf.readInt(3, 100, "N");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
