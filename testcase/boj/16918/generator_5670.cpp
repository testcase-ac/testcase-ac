#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Grid size
    int R = rnd.next(1, 8);
    int C = rnd.next(1, 8);

    // Choose N to cover all modulo-4 cases
    int rem = rnd.next(0, 3);
    int k = rnd.next(0, 4);
    int N;
    if (rem == 0) {
        N = 4 * k;
        if (N == 0) N = 4;
    } else if (rem == 1) {
        N = 4 * k + 1;
    } else if (rem == 2) {
        N = 4 * k + 2;
    } else {
        N = 4 * k + 3;
    }
    N = max(1, min(200, N));

    // Output dimensions and time
    println(R, C, N);

    // Choose an initial pattern type
    int pattern = rnd.next(0, 3);
    double p = rnd.next(0.0, 1.0);

    // Generate the grid
    for (int i = 0; i < R; i++) {
        string row;
        row.reserve(C);
        for (int j = 0; j < C; j++) {
            char ch;
            if (pattern == 0) {
                // random bombs with probability p
                ch = (rnd.next() < p ? 'O' : '.');
            } else if (pattern == 1) {
                // full of bombs
                ch = 'O';
            } else if (pattern == 2) {
                // empty grid
                ch = '.';
            } else {
                // checkerboard with random offset 0 or 1
                int off = rnd.next(0, 1);
                ch = ((i + j + off) % 2 == 0 ? 'O' : '.');
            }
            row.push_back(ch);
        }
        println(row);
    }

    return 0;
}
