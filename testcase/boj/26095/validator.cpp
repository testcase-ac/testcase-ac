#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(2, 300000, "N");
    inf.readEoln();

    vector<int> a = inf.readInts(N, 0, N - 1, "a_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
