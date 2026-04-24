#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read grid size A, B
    int A = inf.readInt(1, 100, "A");
    inf.readSpace();
    int B = inf.readInt(1, 100, "B");
    inf.readEoln();

    // Read number of robots N and number of commands M
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100, "M");
    inf.readEoln();

    // Validate initial robot positions and directions
    // We'll mark occupied positions to ensure uniqueness
    vector< vector<bool> > occupied(A+1, vector<bool>(B+1, false));
    for (int i = 1; i <= N; i++) {
        int x = inf.readInt(1, A, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, B, "y_i");
        inf.readSpace();
        // direction must be one of N, S, E, W
        string dir = inf.readToken("N|S|E|W", "dir_i");
        inf.readEoln();

        // Check distinctness
        ensuref(!occupied[x][y],
                "Initial positions must be distinct: robot %d repeats position (%d, %d)",
                i, x, y);
        occupied[x][y] = true;
    }

    // Validate commands
    for (int j = 1; j <= M; j++) {
        int rid = inf.readInt(1, N, "cmd_robot_j");
        inf.readSpace();
        string cmd = inf.readToken("L|R|F", "cmd_type_j");
        inf.readSpace();
        int rep = inf.readInt(1, 100, "cmd_repeat_j");
        inf.readEoln();
    }

    // Ensure exactly one newline at end of last line and then EOF
    inf.readEof();
    return 0;
}
