#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int maxArea = 20;
    int T = rnd.next(1, 5);
    for (int tc = 0; tc < T; ++tc) {
        int M, N;
        double shapeProb = rnd.next();
        if (shapeProb < 0.3) {
            // single row
            M = 1;
            N = rnd.next(1, maxArea);
        } else if (shapeProb < 0.6) {
            // single column
            N = 1;
            M = rnd.next(1, maxArea);
        } else {
            // general grid with M,N >=2
            do {
                M = rnd.next(2, 10);
                N = rnd.next(2, 10);
            } while (M * N > maxArea);
        }
        // choose candy max value
        int maxCandy;
        double cprob = rnd.next();
        if (cprob < 0.3) {
            maxCandy = rnd.next(1, 5);
        } else if (cprob < 0.6) {
            maxCandy = rnd.next(5, 50);
        } else {
            maxCandy = rnd.next(50, 1000);
        }
        // output dimensions
        println(M, N);
        for (int i = 0; i < M; ++i) {
            vector<int> row;
            for (int j = 0; j < N; ++j) {
                double vprob = rnd.next();
                int v;
                if (vprob < 0.2) {
                    v = rnd.next(1, min(2, maxCandy));
                } else if (vprob < 0.4 && maxCandy >= 2) {
                    v = rnd.next(maxCandy - 1, maxCandy);
                } else {
                    v = rnd.next(1, maxCandy);
                }
                row.push_back(v);
            }
            println(row);
        }
    }
    // termination
    println(0, 0);
    return 0;
}
