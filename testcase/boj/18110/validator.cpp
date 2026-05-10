#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of opinions
    int n = inf.readInt(0, 300000, "n");
    inf.readEoln();

    // Each opinion must be between 1 and 30, one per line
    for (int i = 0; i < n; i++) {
        inf.readInt(1, 30, "a_i");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
