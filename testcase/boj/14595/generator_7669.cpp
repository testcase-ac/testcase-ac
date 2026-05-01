#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter: choose size regime for N
    int mode = rnd.next(0, 2);
    int N;
    if (mode == 0) {
        // small, hand-verifiable
        N = rnd.next(2, 10);
    } else if (mode == 1) {
        // medium
        N = rnd.next(20, 100);
    } else {
        // large with few operations
        N = rnd.next(100000, 1000000);
    }
    // Choose M, with some chance of zero or maximal small
    int M;
    if (rnd.next() < 0.1) {
        M = 0;
    } else if (rnd.next() < 0.1) {
        M = 20;
    } else {
        M = rnd.next(1, 20);
    }
    vector<pair<int,int>> ops;
    double dupProb = 0.15;
    for (int i = 0; i < M; i++) {
        if (!ops.empty() && rnd.next() < dupProb) {
            // duplicate a previous action
            ops.push_back(rnd.any(ops));
        } else {
            // generate new interval
            int type = rnd.next(0, 2);
            int x, y;
            if (type == 0) {
                // adjacent rooms
                x = rnd.next(1, N-1);
                y = x + 1;
            } else if (type == 1) {
                // random arbitrary interval
                x = rnd.next(1, N-1);
                y = rnd.next(x+1, N);
            } else {
                // long interval spanning halves
                int half = N / 2;
                x = rnd.next(1, max(1, half));
                y = rnd.next(half+1, N);
            }
            ops.emplace_back(x, y);
        }
    }
    // occasionally shuffle operations order
    if (rnd.next() < 0.2) {
        shuffle(ops.begin(), ops.end());
    }
    // output
    println(N);
    println((int)ops.size());
    for (auto &p : ops) {
        println(p.first, p.second);
    }
    return 0;
}
