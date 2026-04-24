#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small sizes
    int R = rnd.next(1, 10);
    int C = rnd.next(1, 10);

    // Prepare the top-left design block
    vector<string> block(R, string(C, '.'));
    int pattern = rnd.next(0, 3);
    if (pattern == 0) {
        // random density
        vector<double> dens = {0.2, 0.5, 0.8};
        double pHash = rnd.any(dens);
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                block[i][j] = (rnd.next() < pHash ? '#' : '.');
    } else if (pattern == 1) {
        // all hashes
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                block[i][j] = '#';
    } else if (pattern == 2) {
        // all dots (already initialized)
    } else {
        // checkerboard
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                block[i][j] = ((i + j) % 2 == 0 ? '#' : '.');
    }

    // Single error position
    int A = rnd.next(1, 2 * R);
    int B = rnd.next(1, 2 * C);

    // Output
    println(R, C);
    for (int i = 0; i < R; i++) {
        println(block[i]);
    }
    println(A, B);

    return 0;
}
