#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of saplings N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read growth times t_i
    vector<int> t = inf.readInts(N, 1, 1000000, "t_i");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
