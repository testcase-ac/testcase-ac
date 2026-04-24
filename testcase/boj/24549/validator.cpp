#include "testlib.h"
#include <set>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read grid dimensions and number of soldiers
    int N = inf.readInt(1, 300, "N");
    inf.readSpace();
    int M = inf.readInt(1, 300, "M");
    inf.readSpace();
    long long maxK = (long long)N * M;
    int K = inf.readInt(0, maxK, "K");
    inf.readEoln();

    // Read soldier positions, ensure they are within bounds and no duplicates
    set<pair<int,int>> seen;
    for (int i = 0; i < K; i++) {
        int x = inf.readInt(1, N, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, M, "y_i");
        inf.readEoln();

        pair<int,int> p = make_pair(x, y);
        ensuref(!seen.count(p),
                "Duplicate soldier at index %d: (%d, %d)", i+1, x, y);
        seen.insert(p);
    }

    // No extra data
    inf.readEof();
    return 0;
}
