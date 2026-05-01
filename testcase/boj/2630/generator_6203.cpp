#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose N among powers of two, small enough to verify
    vector<int> Ns = {2, 4, 8, 16};
    int N = rnd.any(Ns);
    // Choose pattern type
    int t = rnd.next(0, 5);
    vector<vector<int>> a(N, vector<int>(N, 0));

    if (t == 0) {
        // All white
        // a already zero
    } else if (t == 1) {
        // All blue
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                a[i][j] = 1;
    } else if (t == 2) {
        // Checkerboard
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                a[i][j] = (i + j) % 2;
    } else if (t == 3) {
        // Vertical stripes
        int maxW = max(1, N/2);
        int w = rnd.next(1, maxW);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                a[i][j] = ((j / w) % 2);
    } else if (t == 4) {
        // Four quadrants, each uniform but not all same
        int half = N / 2;
        vector<int> qc(4);
        for (int i = 0; i < 4; i++)
            qc[i] = rnd.next(0, 1);
        // ensure not all equal
        if (qc[0] == qc[1] && qc[1] == qc[2] && qc[2] == qc[3]) {
            qc[rnd.next(0,3)] ^= 1;
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int qi = (i >= half) + 2*(j >= half);
                a[i][j] = qc[qi];
            }
        }
    } else {
        // Fully random
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                a[i][j] = rnd.next(0, 1);
    }

    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        println(a[i]);
    }
    return 0;
}
