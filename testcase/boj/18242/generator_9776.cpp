#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N, M (keep them small for readability, but varied)
    int shapeType = rnd.next(0, 2);
    int N, M;
    if (shapeType == 0) {
        // Square board
        N = M = rnd.next(5, 20);
    } else if (shapeType == 1) {
        // General rectangle, avoid always equal
        N = rnd.next(5, 20);
        M = rnd.next(5, 20);
        if (N == M) {
            if (N < 20 && rnd.next(0, 1)) M = N + 1;
            else if (N > 5) M = N - 1;
        }
    } else {
        // Strongly rectangular
        if (rnd.next(0, 1) == 0) {
            // Tall
            N = rnd.next(10, 20);
            M = rnd.next(5, 10);
        } else {
            // Wide
            N = rnd.next(5, 10);
            M = rnd.next(10, 20);
        }
    }

    int minSide = min(N, M); // >= 5

    // Choose odd side length L (>=5 and <=minSide), with simple bias
    int maxOdd = (minSide - 5) / 2 + 1; // count of odd lengths: 5,7,...
    int k;
    if (maxOdd == 1) {
        k = 0;
    } else {
        int mode = rnd.next(0, 2);
        if (mode == 0)      k = 0;                // smallest square
        else if (mode == 1) k = maxOdd - 1;       // largest square
        else                k = rnd.next(0, maxOdd - 1); // random in between
    }
    int L = 5 + 2 * k; // actual side length, odd and >=5

    // Choose top-left corner (r0, c0) of the square so that it fits (1-based)
    auto choosePos = [&](int maxPos) -> int {
        if (maxPos <= 2) {
            // Just choose among all valid positions uniformly
            return rnd.next(1, maxPos);
        }
        int mode = rnd.next(0, 2);
        if (mode == 0) return 1;              // stick to one border
        if (mode == 1) return maxPos;         // stick to the opposite border
        // somewhere inside
        return rnd.next(2, maxPos - 1);
    };

    int maxR = N - L + 1;
    int maxC = M - L + 1;
    int r0 = choosePos(maxR);
    int c0 = choosePos(maxC);

    // Initialize grid with '.'
    vector<string> g(N, string(M, '.'));

    // Draw full square border with '#'
    for (int i = 0; i < L; ++i) {
        // top and bottom
        g[r0 - 1][c0 - 1 + i] = '#';
        g[r0 - 1 + L - 1][c0 - 1 + i] = '#';
        // left and right
        g[r0 - 1 + i][c0 - 1] = '#';
        g[r0 - 1 + i][c0 - 1 + L - 1] = '#';
    }

    // Choose orientation of the missing segment: 0=LEFT,1=RIGHT,2=UP,3=DOWN
    int dir = rnd.next(0, 3);
    int mid = L / 2; // offset from 0, center on side

    if (dir == 0) {
        // LEFT
        g[r0 - 1 + mid][c0 - 1] = '.';
    } else if (dir == 1) {
        // RIGHT
        g[r0 - 1 + mid][c0 - 1 + L - 1] = '.';
    } else if (dir == 2) {
        // UP
        g[r0 - 1][c0 - 1 + mid] = '.';
    } else {
        // DOWN
        g[r0 - 1 + L - 1][c0 - 1 + mid] = '.';
    }

    // Output
    println(N, M);
    for (int i = 0; i < N; ++i)
        println(g[i]);

    return 0;
}
