#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters
    int n = rnd.next(1, 10);
    int m = rnd.next(1, 10);
    // density = probability of a blocked cell (1)
    double density = rnd.next(1, 9) / 10.0;
    bool enforcePath = rnd.next(0, 1) == 1;

    // If we enforce a solvable path, build a random lane sequence
    vector<int> lanes;
    if (enforcePath) {
        lanes.resize(m);
        lanes[0] = rnd.next(0, n - 1);
        for (int j = 1; j < m; j++) {
            vector<int> dirs;
            // can always stay
            dirs.push_back(0);
            if (lanes[j-1] > 0) dirs.push_back(-1);
            if (lanes[j-1] < n - 1) dirs.push_back(1);
            int d = rnd.any(dirs);
            lanes[j] = lanes[j-1] + d;
        }
    }

    // Build the grid
    vector< vector<int> > grid(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (enforcePath && lanes[j] == i) {
                // ensure path is clear
                grid[i][j] = 0;
            } else {
                // random block or clear
                grid[i][j] = (rnd.next() < density ? 1 : 0);
            }
        }
    }

    // Output
    println(n, m);
    for (int i = 0; i < n; i++) {
        println(grid[i]);
    }

    return 0;
}
