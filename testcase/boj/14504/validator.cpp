#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read the array A of length N
    vector<int> A = inf.readInts(N, 1, 1000000000, "A");
    inf.readEoln();

    // Read number of queries M
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Read each query
    for (int qi = 0; qi < M; qi++) {
        int type = inf.readInt(1, 2, "type");
        if (type == 1) {
            // Query of form: 1 i j k
            inf.readSpace();
            int i = inf.readInt(1, N, "i");
            inf.readSpace();
            int j = inf.readInt(i, N, "j"); // enforce i <= j
            inf.readSpace();
            int k = inf.readInt(1, 1000000000, "k");
            inf.readEoln();
        } else {
            // Query of form: 2 i k
            inf.readSpace();
            int i = inf.readInt(1, N, "i");
            inf.readSpace();
            int k = inf.readInt(1, 1000000000, "k");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
