#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int scen = rnd.next(0, 4);
    int N;
    vector<vector<int>> A;

    if (scen == 0) {
        // Trivial case N=1
        N = 1;
        A.assign(1, vector<int>(1, rnd.next(0, 1000)));
    } else if (scen == 1) {
        // Maximal uniform values
        N = 4;
        A.assign(N, vector<int>(N, 1000));
    } else if (scen == 2) {
        // Fully random values
        N = rnd.next(2, 4);
        A.assign(N, vector<int>(N));
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                A[i][j] = rnd.next(0, 1000);
    } else if (scen == 3) {
        // Checkerboard high/low pattern
        N = rnd.next(2, 4);
        int high = rnd.next(500, 1000);
        int low  = rnd.next(0, 499);
        A.assign(N, vector<int>(N));
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                A[i][j] = ((i + j) % 2 ? high : low);
    } else {
        // One heavy row, others small
        N = rnd.next(2, 4);
        A.assign(N, vector<int>(N));
        int heavy = rnd.next(0, N - 1);
        for (int j = 0; j < N; j++)
            A[heavy][j] = 1000;
        for (int i = 0; i < N; i++) if (i != heavy)
            for (int j = 0; j < N; j++)
                A[i][j] = rnd.next(0, 100);
    }

    // Output
    println(N);
    for (int i = 0; i < N; i++)
        println(A[i]);

    return 0;
}
