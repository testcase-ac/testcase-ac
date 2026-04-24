#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of columns
    int N = rnd.next(1, 10);
    vector<int> b(N), g(N), w(N);

    // Assign random counts for black, gray, white (0 to 3)
    for (int i = 0; i < N; i++) {
        b[i] = rnd.next(0, 3);
        g[i] = rnd.next(0, 3);
        w[i] = rnd.next(0, 3);
    }

    // Ensure there's at least one can
    int maxH = 0;
    for (int i = 0; i < N; i++) {
        maxH = max(maxH, b[i] + g[i] + w[i]);
    }
    if (maxH == 0) {
        int idx = rnd.next(0, N - 1);
        b[idx] = 1;
        maxH = 1;
    }

    // Number of shots
    int M = rnd.next(1, 10);
    vector<int> shots(M);
    for (int i = 0; i < M; i++) {
        shots[i] = rnd.next(1, maxH);
    }

    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        printf("%d%c", b[i], i + 1 < N ? ' ' : '\n');
    }
    for (int i = 0; i < N; i++) {
        printf("%d%c", g[i], i + 1 < N ? ' ' : '\n');
    }
    for (int i = 0; i < N; i++) {
        printf("%d%c", w[i], i + 1 < N ? ' ' : '\n');
    }
    println(M);
    for (int i = 0; i < M; i++) {
        printf("%d%c", shots[i], i + 1 < M ? ' ' : '\n');
    }

    return 0;
}
