#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases: small for hand-checking
    int T = rnd.next(1, 5);
    for (int tc = 0; tc < T; tc++) {
        // Hyper-parameters for diversity
        int widthBias = rnd.next(-1, 1);
        int heightBias = rnd.next(-1, 1);
        int densityBias = rnd.next(-2, 2);

        // Dimensions
        int w = rnd.wnext(10, widthBias) + 1; // [1..10]
        int h = rnd.wnext(10, heightBias) + 1; // [1..10]

        // Determine land density, with some chance of extremes
        double density;
        int special = rnd.next(0, 4);
        if (special == 0) {
            density = 0.0;
        } else if (special == 1) {
            density = 1.0;
        } else {
            density = rnd.wnext(100, densityBias) / 100.0;
        }

        // Build map
        vector<vector<int>> grid(h, vector<int>(w));
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                grid[i][j] = (rnd.next() < density ? 1 : 0);
            }
        }

        // Output this test case
        println(w, h);
        for (int i = 0; i < h; i++) {
            println(grid[i]);
        }
    }

    // Termination
    println(0, 0);
    return 0;
}
