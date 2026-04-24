#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for grid size N: bias towards small or large
    int N;
    if (rnd.next(0, 1) == 0)
        N = rnd.wnext(10, 1) + 1;   // bias to larger N
    else
        N = rnd.wnext(10, -1) + 1;  // bias to smaller N

    // Number of points M, at most 20 and at most N*N
    int maxM = min(N * N, 20);
    int M = rnd.next(1, maxM);

    vector<pair<int,int>> pts;
    // Decide if we generate a cluster or full random
    if (rnd.next() < 0.5) {
        // Cluster mode
        int centerR = rnd.next(1, N);
        int centerC = rnd.next(1, N);
        for (int i = 0; i < M; i++) {
            if (rnd.next() < 0.7) {
                // Around the center within a small window
                int dr = rnd.next(-2, 2);
                int dc = rnd.next(-2, 2);
                int r = min(max(centerR + dr, 1), N);
                int c = min(max(centerC + dc, 1), N);
                pts.emplace_back(r, c);
            } else {
                // Some random noise
                int r = rnd.next(1, N);
                int c = rnd.next(1, N);
                pts.emplace_back(r, c);
            }
        }
    } else {
        // Fully random points
        for (int i = 0; i < M; i++) {
            int r = rnd.next(1, N);
            int c = rnd.next(1, N);
            pts.emplace_back(r, c);
        }
    }

    // Shuffle the list of points for randomness
    shuffle(pts.begin(), pts.end());

    // Output
    println(N, M);
    for (auto &p : pts)
        println(p.first, p.second);

    return 0;
}
