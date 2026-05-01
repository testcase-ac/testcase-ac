#include "testlib.h"
#include <vector>
#include <string>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of initial shapes
    int N = rnd.next(1, 10);
    // Number of operations: mix small, medium, larger counts
    double mode = rnd.next();
    int M;
    if (mode < 0.3) M = rnd.next(1, 5);
    else if (mode < 0.6) M = rnd.next(6, 15);
    else M = rnd.next(16, 25);

    // Generate initial one-layer shapes
    string types = "CRWS";
    string colors = "rgbypcuw";
    vector<string> init;
    for (int i = 0; i < N; i++) {
        double fillProb = rnd.next(0.0, 1.0);
        string layer;
        int filled = 0;
        for (int q = 0; q < 4; q++) {
            if (rnd.next() < fillProb) {
                layer += rnd.any(types);
                layer += rnd.any(colors);
                filled++;
            } else {
                layer += "--";
            }
        }
        // Ensure at least one quadrant is filled
        if (filled == 0) {
            int q = rnd.next(0, 3);
            layer[2*q] = rnd.any(types);
            layer[2*q+1] = rnd.any(colors);
        }
        init.push_back(layer);
    }

    // Output header
    println(N, M);
    // Output initial shapes
    for (auto &s : init) println(s);

    // Generate operations
    string colOps = "rgbypcw";
    for (int op = 0; op < M; op++) {
        int type = rnd.next(1, 4);
        if (type == 1) {
            // cut: 1 i j k, j!=k
            int i = rnd.next(1, 100);
            int j = rnd.next(1, 100);
            int k = rnd.next(1, 100);
            while (k == j) k = rnd.next(1, 100);
            println(1, i, j, k);
        } else if (type == 2) {
            // rotate: 2 i j k (k in 1..3)
            int i = rnd.next(1, 100);
            int j = rnd.next(1, 100);
            int k = rnd.next(1, 3);
            println(2, i, j, k);
        } else if (type == 3) {
            // merge: 3 i j k
            int i = rnd.next(1, 100);
            int j = rnd.next(1, 100);
            int k = rnd.next(1, 100);
            println(3, i, j, k);
        } else {
            // color: 4 i j color
            int i = rnd.next(1, 100);
            int j = rnd.next(1, 100);
            char c = rnd.any(colOps);
            // cannot color with 'u'
            while (c == 'u') c = rnd.any(colOps);
            printf("4 %d %d %c\n", i, j, c);
        }
    }
    return 0;
}
