#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n: number of knights in each house
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    // Read challenges f_i issued by knights 1..n to knights in house 2
    // Each f_i should be in [n+1, 2n]
    vector<int> f = inf.readInts(n, n+1, 2*n, "f_i");
    inf.readEoln();

    // Read challenges s_i issued by knights n+1..2n to knights in house 1
    // Each s_i should be in [1, n]
    vector<int> s = inf.readInts(n, 1, n, "s_i");
    inf.readEoln();

    // No additional global checks are needed:
    // It's guaranteed by problem that a kernel exists (theorem for bipartite functional graphs).

    inf.readEof();
    return 0;
}
