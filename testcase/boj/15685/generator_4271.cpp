#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of dragon curves
    int N = rnd.next(1, 10);
    println(N);

    for (int i = 0; i < N; i++) {
        // Hyper-parameter for generation: weighted to get small or large g
        int t = rnd.any(vector<int>{-1, 0, 1});
        // We'll limit g to [0,5] to ensure the curve stays within [0,100]
        int g = rnd.wnext(6, t);  // rnd.wnext(6, t) gives [0..5]

        // Starting direction
        int d = rnd.next(0, 3);

        // Build the sequence of directions for g generations
        vector<int> dirs;
        dirs.push_back(d);
        for (int gen = 1; gen <= g; gen++) {
            int sz = dirs.size();
            for (int j = sz - 1; j >= 0; j--) {
                dirs.push_back((dirs[j] + 1) % 4);
            }
        }

        // Compute the bounding box of the curve when starting at (0,0)
        int cx = 0, cy = 0;
        int minx = 0, maxx = 0, miny = 0, maxy = 0;
        for (int dir : dirs) {
            // 0:→, 1:↑, 2:←, 3:↓
            if (dir == 0) cx++;
            else if (dir == 1) cy--;
            else if (dir == 2) cx--;
            else if (dir == 3) cy++;
            minx = min(minx, cx);
            maxx = max(maxx, cx);
            miny = min(miny, cy);
            maxy = max(maxy, cy);
        }

        // Choose start (x,y) so that the entire curve stays within [0,100]
        int lo_x = -minx;
        int hi_x = 100 - maxx;
        int lo_y = -miny;
        int hi_y = 100 - maxy;
        int x = rnd.next(lo_x, hi_x);
        int y = rnd.next(lo_y, hi_y);

        println(x, y, d, g);
    }

    return 0;
}
