#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of eggs
    int N = inf.readInt(1, 8, "N");
    inf.readEoln();

    // For each egg, read durability S_i and weight W_i
    for (int i = 0; i < N; i++) {
        int S = inf.readInt(1, 300, "S_i");
        inf.readSpace(); // exactly one space as per statement
        int W = inf.readInt(1, 300, "W_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
