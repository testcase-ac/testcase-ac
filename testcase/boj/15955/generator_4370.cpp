#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small sizes
    int N = rnd.next(1, 10);
    int Q = rnd.next(1, 20);

    // Compute minimum C so that (2*C+1)^2 >= N
    int Cmin = 0;
    while ((2 * Cmin + 1) * (2 * Cmin + 1) < N) {
        ++Cmin;
    }
    int Cmax = max(Cmin, 10);
    int C = rnd.next(Cmin, Cmax);

    // Prepare all possible distinct checkpoint coordinates
    vector<pair<int,int>> cells;
    for (int x = -C; x <= C; ++x) {
        for (int y = -C; y <= C; ++y) {
            cells.emplace_back(x, y);
        }
    }
    shuffle(cells.begin(), cells.end());
    cells.resize(N);

    // Output N, Q and the checkpoints
    println(N, Q);
    for (auto &p : cells) {
        println(p.first, p.second);
    }

    // Generate diverse queries
    for (int i = 0; i < Q; ++i) {
        int A = rnd.next(1, N);
        int B = rnd.next(1, N);
        double prob = rnd.next();
        int X;
        if (prob < 0.2) {
            X = 0;
        } else if (prob < 0.4) {
            X = rnd.next(1, 2);
        } else if (prob < 0.6) {
            X = rnd.next(3, 10);
        } else if (prob < 0.8) {
            X = rnd.next(20, 100);
        } else {
            X = rnd.next(100, 1000000000);
        }
        println(A, B, X);
    }

    return 0;
}
