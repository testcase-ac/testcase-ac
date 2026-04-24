#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 3);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // number of folks and days
        int n = rnd.next(1, 10);
        int m = rnd.next(0, 10);
        // Random coordinate bounds (small, biased to smaller)
        int boundX = rnd.wnext(21, -1);
        int boundY = rnd.wnext(21, -1);
        println(n, m);
        // Generate n points, allowing repeats
        for (int i = 0; i < n; i++) {
            int x = rnd.next(0, boundX);
            int y = rnd.next(0, boundY);
            println(x, y);
        }
        // Generate m query rectangles
        for (int i = 0; i < m; i++) {
            int l = rnd.next(0, boundX);
            int r = rnd.next(l, boundX);
            int b = rnd.next(0, boundY);
            int t = rnd.next(b, boundY);
            println(l, r, b, t);
        }
    }
    return 0;
}
