#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read L and G
    int L = inf.readInt(1, 8000, "L");
    inf.readSpace();
    int G = inf.readInt(1, 800, "G");
    inf.readEoln();

    // Read the escape strengths C_i
    vector<long long> C = inf.readLongs(L, 1LL, 1000000000LL, "C_i");
    inf.readEoln();

    // No extra tokens
    inf.readEof();
    return 0;
}
