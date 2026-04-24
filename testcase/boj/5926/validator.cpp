#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of cows
    int N = inf.readInt(1, 50000, "N");
    inf.readEoln();

    // Read each cow: x coordinate and breed ID
    for (int i = 0; i < N; i++) {
        // x coordinate: positive integer up to 1e9
        inf.readInt(1, 1000000000, "x_i");
        inf.readSpace();
        // breed ID: positive integer up to 1e9
        inf.readInt(1, 1000000000, "breed_i");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
