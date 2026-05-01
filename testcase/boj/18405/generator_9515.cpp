#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N;
    int S, X, Y;
    int maxVirus = 0;
    vector<vector<int>> a;

    int scenario = rnd.next(0, 7);

    if (scenario == 0) {
        // Single virus
        N = rnd.next(1, 5);
        a.assign(N, vector<int>(N, 0));
        int vx = rnd.next(0, N - 1);
        int vy = rnd.next(0, N - 1);
        int vid = rnd.next(1, 9);
        a[vx][vy] = vid;
        maxVirus = vid;

        S = rnd.next(0, 2 * N);
        if (rnd.next(0, 1) == 0) {
            X = vx + 1;
            Y = vy + 1;
        } else {
            X = rnd.next(1, N);
            Y = rnd.next(1, N);
        }
    } else if (scenario == 1) {
        // Conflict at center, smaller index wins
        N = 5;
        a.assign(N, vector<int>(N, 0));
        a[0][2] = 1;
        a[2][0] = 2;
        a[2][4] = 3;
        a[4][2] = 4;
        maxVirus = 4;

        S = rnd.next(1, 7);
        X = 3;
        Y = 3;
    } else if (scenario == 2) {
        // Random sparse grid
        N = rnd.next(4, 9);
        a.assign(N, vector<int>(N, 0));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (rnd.next(0, 3) == 0) { // ~25% cells with virus
                    int vid = rnd.next(1, 9);
                    a[i][j] = vid;
                    if (vid > maxVirus) maxVirus = vid;
                }
            }
        }
        if (maxVirus == 0) {
            int rx = rnd.next(0, N - 1);
            int ry = rnd.next(0, N - 1);
            int vid = rnd.next(1, 9);
            a[rx][ry] = vid;
            maxVirus = vid;
        }
        S = rnd.next(0, 2 * N + 3);
        X = rnd.next(1, N);
        Y = rnd.next(1, N);
    } else if (scenario == 3) {
        // Random dense grid
        N = rnd.next(4, 9);
        a.assign(N, vector<int>(N, 0));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (rnd.next(0, 9) < 7) { // ~70% cells with virus
                    int vid = rnd.next(1, 9);
                    a[i][j] = vid;
                    if (vid > maxVirus) maxVirus = vid;
                }
            }
        }
        if (maxVirus == 0) {
            int rx = rnd.next(0, N - 1);
            int ry = rnd.next(0, N - 1);
            int vid = rnd.next(1, 9);
            a[rx][ry] = vid;
            maxVirus = vid;
        }
        S = rnd.next(0, 2 * N + 3);
        X = rnd.next(1, N);
        Y = rnd.next(1, N);
    } else if (scenario == 4) {
        // All zeros (no virus)
        N = rnd.next(1, 9);
        a.assign(N, vector<int>(N, 0));
        maxVirus = 0;
        S = rnd.next(0, 20);
        X = rnd.next(1, N);
        Y = rnd.next(1, N);
    } else if (scenario == 5) {
        // Full grid with repeating pattern of virus types
        N = rnd.next(2, 9);
        a.assign(N, vector<int>(N, 0));
        int cur = 1;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                a[i][j] = cur;
                if (cur > maxVirus) maxVirus = cur;
                cur++;
                if (cur == 10) cur = 1;
            }
        }
        S = rnd.next(0, 2 * N + 3);
        X = rnd.next(1, N);
        Y = rnd.next(1, N);
    } else if (scenario == 6) {
        // S = 0 case
        N = rnd.next(1, 9);
        a.assign(N, vector<int>(N, 0));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (rnd.next(0, 1) == 0) { // ~50% cells with virus
                    int vid = rnd.next(1, 9);
                    a[i][j] = vid;
                    if (vid > maxVirus) maxVirus = vid;
                }
            }
        }
        // It's fine if there are no viruses here (still valid)
        S = 0;
        X = rnd.next(1, N);
        Y = rnd.next(1, N);
    } else {
        // scenario == 7: target unreachable within S
        N = rnd.next(4, 9);
        a.assign(N, vector<int>(N, 0));
        int vid = rnd.next(1, 9);
        a[0][0] = vid;
        maxVirus = vid;

        int dist = 2 * (N - 1); // distance from (1,1) to (N,N)
        int hi = dist - 1;      // ensure S < dist
        S = rnd.next(0, hi);
        X = N;
        Y = N;
    }

    int K;
    if (maxVirus == 0) {
        K = rnd.next(1, 20);
    } else {
        int upper = min(1000, maxVirus + 20);
        K = rnd.next(maxVirus, upper);
    }

    println(N, K);
    for (int i = 0; i < N; i++) {
        println(a[i]);
    }
    println(S, X, Y);

    return 0;
}
