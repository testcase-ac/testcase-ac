#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Grid size hyper-parameter
    int N = rnd.next(1, 8);

    // Different height distributions for variability
    int mode = rnd.next(1, 5);
    vector<vector<int>> a(N, vector<int>(N));

    if (mode == 1) {
        // Small uniform heights [0,10]
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                a[i][j] = rnd.next(0, 10);

    } else if (mode == 2) {
        // Medium uniform heights [0,1000]
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                a[i][j] = rnd.next(0, 1000);

    } else if (mode == 3) {
        // Sparse heavy: most zeros, some huge values up to 1e7
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                a[i][j] = (rnd.next(0, 3) == 0 ? rnd.next(0, 10000000) : 0);

    } else if (mode == 4) {
        // One dominant cell and small elsewhere
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                a[i][j] = rnd.next(0, 10);
        int x = rnd.next(0, N - 1);
        int y = rnd.next(0, N - 1);
        a[x][y] = rnd.next(1000000, 10000000);

    } else {
        // Sorted distribution: increasing or decreasing
        vector<int> flat;
        flat.reserve(N * N);
        for (int i = 0; i < N * N; i++)
            flat.push_back(rnd.next(0, 1000));
        sort(flat.begin(), flat.end());
        if (rnd.next(0, 1) == 1)
            reverse(flat.begin(), flat.end());
        for (int i = 0, p = 0; i < N; i++)
            for (int j = 0; j < N; j++, p++)
                a[i][j] = flat[p];
    }

    // Output
    println(N);
    for (int i = 0; i < N; i++)
        println(a[i]);

    return 0;
}
