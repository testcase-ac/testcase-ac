#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N;
    int p = rnd.next(1, 100);

    // Base distribution for N
    if (p <= 50) {
        // Small, hand-checkable
        N = rnd.next(6, 12);
    } else if (p <= 80) {
        // Medium
        N = rnd.next(13, 30);
    } else if (p <= 95) {
        // Larger but still moderate
        N = rnd.next(31, 100);
    } else {
        // Big
        N = rnd.next(101, 666);
    }

    // Occasionally force special sizes (corners of constraints, etc.)
    if (rnd.next(0, 4) == 0) {
        vector<int> special = {6, 7, 8, 9, 10, 11, 12, 666};
        N = rnd.any(special);
    }

    int r, c;
    int style = rnd.next(0, 4);

    switch (style) {
        case 0: {
            // Completely random start
            r = rnd.next(1, N);
            c = rnd.next(1, N);
            break;
        }
        case 1: {
            // Random corner
            vector<pair<int,int>> corners = {
                {1, 1}, {1, N}, {N, 1}, {N, N}
            };
            auto pnt = rnd.any(corners);
            r = pnt.first;
            c = pnt.second;
            break;
        }
        case 2: {
            // Random edge but not a corner
            int side = rnd.next(0, 3);
            if (side == 0) { // top
                r = 1;
                c = rnd.next(2, N - 1);
            } else if (side == 1) { // bottom
                r = N;
                c = rnd.next(2, N - 1);
            } else if (side == 2) { // left
                r = rnd.next(2, N - 1);
                c = 1;
            } else { // right
                r = rnd.next(2, N - 1);
                c = N;
            }
            break;
        }
        case 3: {
            // Near the center
            int lo = N / 2;
            int hi = N / 2 + 1;
            if (hi > N) hi = N;
            r = rnd.next(lo, hi);
            c = rnd.next(lo, hi);
            break;
        }
        case 4: {
            // On first or last row, random column
            r = (rnd.next(0, 1) == 0 ? 1 : N);
            c = rnd.next(1, N);
            break;
        }
    }

    println(N);
    println(r, c);

    return 0;
}
