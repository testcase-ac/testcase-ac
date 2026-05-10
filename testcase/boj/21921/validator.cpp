#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and X
    int N = inf.readInt(1, 250000, "N");
    inf.readSpace();
    int X = inf.readInt(1, N, "X");
    inf.readEoln();

    // Read visitor counts for N days
    vector<int> v = inf.readInts(N, 0, 8000, "visitors");
    inf.readEoln();

    // No further global properties to check
    inf.readEof();
    return 0;
}
