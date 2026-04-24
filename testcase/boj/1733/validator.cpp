#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of T-shirts
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    // For each T-shirt, read the pair of numbers (inside, outside)
    for (int i = 0; i < N; i++) {
        inf.readInt(1, 1000000, "inside_number");
        inf.readSpace();
        inf.readInt(1, 1000000, "outside_number");
        inf.readEoln();
    }

    // No extra data allowed
    inf.readEof();
    return 0;
}
