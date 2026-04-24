#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Grid size
    int N = rnd.next(4, 12);
    // Number of moves: sometimes small, sometimes large
    int K;
    if (rnd.next(0, 1) == 0) K = rnd.next(1, 20);
    else K = rnd.next(500, 1000);
    // Number of fireballs, varied by weighted sampling
    int maxM = N * N;
    vector<int> tvals = { -2, 0, 2 };
    int w = rnd.any(tvals);
    int M = rnd.wnext(maxM + 1, w); // [0..N*N]
    // prepare distinct positions
    vector<int> cells(N*N);
    for (int i = 0; i < N*N; i++) cells[i] = i;
    shuffle(cells.begin(), cells.end());
    // Output
    println(N, M, K);
    for (int i = 0; i < M; i++) {
        int id = cells[i];
        int r = id / N + 1;
        int c = id % N + 1;
        // mass: weighted, ensure >=1
        int wm = rnd.any(tvals);
        int m = rnd.wnext(1000, wm) + 1; // [1..1000]
        // speed: sometimes small (wrap), sometimes moderate
        int s;
        if (rnd.next(0,1) == 0) {
            s = rnd.next(1, N * 3);
        } else {
            s = rnd.next(N * 3, N * 10);
        }
        // direction
        int d = rnd.next(0, 7);
        println(r, c, m, s, d);
    }
    return 0;
}
