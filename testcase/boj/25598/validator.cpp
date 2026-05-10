#include "testlib.h"
#include <set>
#include <vector>
#include <string>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(3, 25, "N");
    inf.readEoln();

    // 2. Read O (length of command string)
    string commands = inf.readToken("[UDLRS]{1,10000}", "commands");
    int O = commands.size();
    inf.readEoln();

    // 3. Read player start position
    int p_y = inf.readInt(1, N, "p_y");
    inf.readSpace();
    int p_x = inf.readInt(1, N, "p_x");
    inf.readEoln();

    // 4. Read W (number of walls)
    int W = inf.readInt(0, N*N-1, "W");
    inf.readEoln();

    set<pair<int,int>> wall_set;
    for (int i = 0; i < W; ++i) {
        int w_y = inf.readInt(1, N, "w_y");
        inf.readSpace();
        int w_x = inf.readInt(1, N, "w_x");
        inf.readEoln();
        ensuref(!(w_y == p_y && w_x == p_x),
            "Wall at (%d,%d) coincides with player start position (%d,%d)", w_y, w_x, p_y, p_x);
        ensuref(!wall_set.count({w_y, w_x}),
            "Duplicate wall at (%d,%d)", w_y, w_x);
        wall_set.insert({w_y, w_x});
    }

    // 5. Read Z (number of zombies)
    int Z = inf.readInt(0, N*N-1-W, "Z");
    inf.readEoln();

    set<pair<int,int>> zombie_set;
    for (int i = 0; i < Z; ++i) {
        int z_y = inf.readInt(1, N, "z_y");
        inf.readSpace();
        int z_x = inf.readInt(1, N, "z_x");
        inf.readSpace();
        int z_type = inf.readInt(0, 1, "z_type");
        inf.readSpace();
        string z_dir = inf.readToken("[UDLR]", "z_dir");
        inf.readSpace();
        if (z_type == 0) {
            int l = inf.readInt(0, N, "l");
        } else {
            long long h = inf.readLong(0LL, 100000000LL, "h");
        }
        inf.readEoln();

        ensuref(!(z_y == p_y && z_x == p_x),
            "Zombie at (%d,%d) coincides with player start position (%d,%d)", z_y, z_x, p_y, p_x);
        ensuref(!wall_set.count({z_y, z_x}),
            "Zombie at (%d,%d) coincides with wall", z_y, z_x);
        ensuref(!zombie_set.count({z_y, z_x}),
            "Duplicate zombie at (%d,%d)", z_y, z_x);
        zombie_set.insert({z_y, z_x});
    }

    // 6. Read D (day to check)
    int D = inf.readInt(1, O, "D");
    inf.readEoln();

    inf.readEof();
}
