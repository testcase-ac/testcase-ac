#include "testlib.h"
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of pillars
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    vector<int> Ls(N), Hs(N);
    set<int> usedL;
    for (int i = 0; i < N; i++) {
        // Read position and height
        int L = inf.readInt(1, 1000, "L_i");
        inf.readSpace();
        int H = inf.readInt(1, 1000, "H_i");
        inf.readEoln();

        // No two pillars should share the same left position
        ensuref(!usedL.count(L),
                "Duplicate pillar position L=%d at line %d", L, i + 2);
        usedL.insert(L);

        Ls[i] = L;
        Hs[i] = H;
    }

    inf.readEof();
    return 0;
}
