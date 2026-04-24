#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and k
    int n = inf.readInt(2, 2500, "n");
    inf.readSpace();
    int k = inf.readInt(2, n, "k");
    inf.readEoln();

    // Read parent pointers for nodes 1..n-1
    for (int i = 1; i < n; i++) {
        // p_i must satisfy 0 <= p_i < i
        int p = inf.readInt(0, i - 1, "p_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
