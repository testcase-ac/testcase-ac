#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of helmets N and vests M
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000, "M");
    inf.readEoln();

    // Read helmet defenses h[i]
    inf.readLongs(N, 1LL, 1000000000LL, "h_i");
    inf.readEoln();

    // Read vest defenses a[i]
    inf.readLongs(M, 1LL, 1000000000LL, "a_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
