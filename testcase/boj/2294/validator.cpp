#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and k
    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int k = inf.readInt(1, 10000, "k");
    inf.readEoln();

    // Read coin values
    for (int i = 0; i < n; i++) {
        // Each coin value is a positive integer up to 100000
        inf.readInt(1, 100000, "coin");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
