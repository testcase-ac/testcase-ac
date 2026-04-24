#include "testlib.h"
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, W, C, H, M
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int W = inf.readInt(1, 8000, "W");
    inf.readSpace();
    int C = inf.readInt(1, 20, "C");
    inf.readSpace();
    int H = inf.readInt(1, N, "H");
    inf.readSpace();
    int M = inf.readInt(1, N, "M");
    inf.readEoln();

    // Read human-controlled systems
    vector<int> humans = inf.readInts(H, 0, N-1, "human_system");
    inf.readEoln();
    // Check for duplicates in human-controlled
    {
        set<int> seen;
        for (int i = 0; i < H; i++) {
            int x = humans[i];
            bool inserted = seen.insert(x).second;
            ensuref(inserted,
                    "Duplicate human-controlled system at index %d: %d", i, x);
        }
    }

    // Read military bases
    vector<int> bases = inf.readInts(M, 0, N-1, "military_base");
    inf.readEoln();
    // Check for duplicates in military bases
    {
        set<int> seen;
        for (int i = 0; i < M; i++) {
            int x = bases[i];
            bool inserted = seen.insert(x).second;
            ensuref(inserted,
                    "Duplicate military base at index %d: %d", i, x);
        }
    }

    // Read W wormholes
    for (int i = 0; i < W; i++) {
        int s = inf.readInt(0, N-1, "s_i");
        inf.readSpace();
        int c = inf.readInt(1, C, "c_i");
        inf.readSpace();
        int t = inf.readInt(0, N-1, "t_i");
        inf.readEoln();
        // Loops (s == t) and multiple edges are allowed by problem statement
    }

    inf.readEof();
    return 0;
}
