#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Grid dimensions: small, medium, or large
    int R, C;
    double dr = rnd.next();
    if (dr < 0.3) {
        R = rnd.next(2, 5);
    } else if (dr < 0.6) {
        R = rnd.next(6, 10);
    } else {
        R = rnd.next(11, 20);
    }
    double dc = rnd.next();
    if (dc < 0.3) {
        C = rnd.next(2, 5);
    } else if (dc < 0.6) {
        C = rnd.next(6, 10);
    } else {
        C = rnd.next(11, 20);
    }
    // Alphabet size
    int K = rnd.next(2, 26); // use letters 'a' to 'a'+K-1
    // Block density hyperparameters: sometimes none, sometimes full, else random
    double pBlock;
    double d = rnd.next();
    if (d < 0.15) {
        pBlock = 0.0;
    } else if (d < 0.30) {
        pBlock = 1.0;
    } else {
        pBlock = rnd.next();
    }
    // Initialize grid
    vector<string> g(R, string(C, '#'));
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (rnd.next() < pBlock) {
                g[i][j] = '#';
            } else {
                g[i][j] = char('a' + rnd.next(K - 1));
            }
        }
    }
    // Ensure at least one word of length >= 2
    if (rnd.next(0,1) == 0) {
        // horizontal
        int r0 = rnd.next(0, R - 1);
        int c0 = rnd.next(0, C - 2);
        int maxL = C - c0;
        int L = rnd.next(2, maxL);
        for (int j = c0; j < c0 + L; j++) {
            g[r0][j] = char('a' + rnd.next(K - 1));
        }
    } else {
        // vertical
        int c0 = rnd.next(0, C - 1);
        int r0 = rnd.next(0, R - 2);
        int maxL = R - r0;
        int L = rnd.next(2, maxL);
        for (int i = r0; i < r0 + L; i++) {
            g[i][c0] = char('a' + rnd.next(K - 1));
        }
    }
    // Output
    println(R, C);
    for (int i = 0; i < R; i++) {
        println(g[i]);
    }
    return 0;
}
