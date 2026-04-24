#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(2, 400, "N");
    inf.readSpace();
    int K = inf.readInt(1, N - 1, "K");
    inf.readEoln();

    // Read the snake group sizes
    vector<int> a = inf.readInts(N, 0, 1000000, "a_i");
    inf.readEoln();

    // No more tokens
    inf.readEof();
    return 0;
}
