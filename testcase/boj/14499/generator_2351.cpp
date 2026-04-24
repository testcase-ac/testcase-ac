#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Grid size
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 10);
    // Starting position
    int x = rnd.next(0, N - 1);
    int y = rnd.next(0, M - 1);
    // Number of commands
    int K = rnd.next(1, 20);

    // Generate map with values 0..9, ensure start cell is 0
    vector<vector<int>> a(N, vector<int>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            a[i][j] = rnd.next(0, 9);
        }
    }
    a[x][y] = 0;

    // Generate command sequence (1=E,2=W,3=N,4=S)
    vector<int> cmd(K);
    for (int i = 0; i < K; i++) {
        cmd[i] = rnd.next(1, 4);
    }

    // Output
    println(N, M, x, y, K);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d%c", a[i][j], j + 1 < M ? ' ' : '\n');
        }
    }
    for (int i = 0; i < K; i++) {
        printf("%d%c", cmd[i], i + 1 < K ? ' ' : '\n');
    }

    return 0;
}
