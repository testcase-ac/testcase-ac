#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of cupboards
    int n = inf.readInt(3, 20, "n");
    inf.readEoln();

    // Read the two initially open cupboards
    vector<int> open = inf.readInts(2, 1, n, "open");
    inf.readEoln();
    ensuref(open[0] != open[1],
            "Initially open cupboard positions must be distinct, got %d and %d",
            open[0], open[1]);

    // Read the length of the use-sequence
    int k = inf.readInt(1, 20, "k");
    inf.readEoln();

    // Read each cupboard to be used in order
    for (int i = 0; i < k; i++) {
        // name it for clarity in error messages
        string nm = "order_" + to_string(i+1);
        int v = inf.readInt(1, n, nm.c_str());
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
