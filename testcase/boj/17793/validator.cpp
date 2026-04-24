#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of players n: 2 ≤ n ≤ 50
    int n = inf.readInt(2, 50, "n");
    inf.readSpace();
    // Read number of lives k: 1 ≤ k ≤ 50
    int k = inf.readInt(1, 50, "k");
    inf.readSpace();
    // Read probability p: 0.1 ≤ p ≤ 0.9
    double p = inf.readDouble(0.1, 0.9, "p");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
