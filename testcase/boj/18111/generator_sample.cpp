#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int N = rnd.next(1, 6);
    int M = rnd.next(1, 6);
    vector<vector<int>> height(N, vector<int>(M));

    if (mode == 0) {
        int h = rnd.next(0, 256);
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                height[i][j] = h;
    } else if (mode == 1) {
        int low = rnd.next(0, 255);
        int high = low + 1;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                height[i][j] = rnd.next(0, 1) ? high : low;
    } else if (mode == 2) {
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                height[i][j] = ((i + j + rnd.next(0, 1)) % 2) ? 256 : 0;
    } else if (mode == 3) {
        int base = rnd.next(0, 256);
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                height[i][j] = base;
        height[rnd.next(0, N - 1)][rnd.next(0, M - 1)] = rnd.next(0, 1) ? 0 : 256;
    } else if (mode == 4) {
        int low = rnd.next(0, 220);
        int high = rnd.next(low, min(256, low + rnd.next(3, 36)));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                height[i][j] = rnd.next(low, high);
    } else {
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                height[i][j] = rnd.next(0, 256);
    }

    long long totalBlocks = 0;
    for (const auto& row : height)
        for (int h : row)
            totalBlocks += h;

    vector<long long> inventoryChoices = {0LL, 1LL, totalBlocks / 2, totalBlocks, 64000000LL};
    long long B = rnd.any(inventoryChoices);

    println(N, M, B);
    for (const auto& row : height)
        println(row);

    return 0;
}
