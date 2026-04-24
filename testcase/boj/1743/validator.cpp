#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read grid dimensions and number of food wastes
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100, "M");
    inf.readSpace();
    long long maxK = 1LL * N * M;
    int K = inf.readInt(1, maxK, "K");
    inf.readEoln();

    // Read and validate K distinct coordinates
    set<pair<int,int>> coords;
    for (int i = 0; i < K; i++) {
        int r = inf.readInt(1, N, "r_i");
        inf.readSpace();
        int c = inf.readInt(1, M, "c_i");
        inf.readEoln();

        // Check for duplicates
        pair<int,int> p = {r, c};
        ensuref(!coords.count(p),
                "Duplicate coordinate at input line %d: (%d, %d)", 
                i + 2, r, c);
        coords.insert(p);
    }

    // No extra data
    inf.readEof();
    return 0;
}
