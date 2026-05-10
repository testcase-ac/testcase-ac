#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of buildings
    int N = inf.readInt(1, 80000, "N");
    inf.readEoln();

    // Heights of the buildings
    for (int i = 1; i <= N; i++) {
        inf.readLong(1LL, 1000000000LL, "h");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
