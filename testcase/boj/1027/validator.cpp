#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of buildings N
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    // Read heights of the N buildings
    vector<long long> h = inf.readLongs(N, 1LL, 1000000000LL, "h");
    inf.readEoln();

    // No further constraints to check (simple input)
    inf.readEof();
    return 0;
}
