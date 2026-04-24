#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose density mode for 'S'
    int mode = rnd.next(0, 2); // 0 = low, 1 = mid, 2 = high
    double p;
    if (mode == 0) {
        // low S density [0,0.3)
        p = rnd.next() * 0.3;
    } else if (mode == 1) {
        // medium S density [0.3,0.7)
        p = 0.3 + rnd.next() * 0.4;
    } else {
        // high S density [0.7,1.0)
        p = 0.7 + rnd.next() * 0.3;
    }

    // Generate grid
    vector<string> grid(5, string(5, 'Y'));
    int sCount = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (rnd.next() < p) {
                grid[i][j] = 'S';
                sCount++;
            }
        }
    }

    // Ensure at least 4 'S' exist to allow non-trivial solutions
    if (sCount < 4) {
        // pick random positions to flip to 'S'
        vector<pair<int,int>> pos;
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                if (grid[i][j] == 'Y')
                    pos.emplace_back(i, j);
        shuffle(pos.begin(), pos.end());
        for (int k = 0; k < 4 - sCount && k < (int)pos.size(); k++) {
            auto pr = pos[k];
            grid[pr.first][pr.second] = 'S';
        }
    }

    // Output the 5x5 grid
    for (int i = 0; i < 5; i++) {
        println(grid[i]);
    }
    return 0;
}
