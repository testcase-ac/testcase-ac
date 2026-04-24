#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; ++tc) {
        // Number of rectangles
        int n = rnd.next(1, 10);
        // Maximum coordinate value
        int C = rnd.next(1, 50);
        println(n);
        // Hyper-parameters for skewing width and height distributions
        int tw = rnd.any(vector<int>{-3, -1, 0, 1, 3});
        int th = rnd.any(vector<int>{-3, -1, 0, 1, 3});
        for (int i = 0; i < n; ++i) {
            // Generate width and height biased by tw, th
            int w = rnd.wnext(C, tw) + 1;
            int h = rnd.wnext(C, th) + 1;
            // Place rectangle within [0, C] x [0, C]
            int x1 = rnd.next(0, C - w);
            int y1 = rnd.next(0, C - h);
            int x2 = x1 + w;
            int y2 = y1 + h;
            println(x1, y1, x2, y2);
        }
    }

    return 0;
}
