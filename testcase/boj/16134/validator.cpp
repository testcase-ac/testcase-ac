#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and R with strict bounds and formatting
    int N = inf.readInt(0, 1000000, "N");
    inf.readSpace();
    int R = inf.readInt(0, 1000000, "R");
    inf.readEoln();

    // Validate the implied constraint R <= N
    ensuref(R <= N, "R must be <= N, but got N = %d and R = %d", N, R);

    // No extra data
    inf.readEof();
    return 0;
}
