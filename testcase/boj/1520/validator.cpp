#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions
    int M = inf.readInt(1, 500, "M");
    inf.readSpace();
    int N = inf.readInt(1, 500, "N");
    inf.readEoln();

    // Read height map
    vector<int> hgt;
    hgt.reserve((long long)M * N);
    for (int i = 0; i < M; i++) {
        vector<int> row = inf.readInts(N, 1, 10000, "height");
        inf.readEoln();
        for (int v : row) {
            hgt.push_back(v);
        }
    }

    // Build list of cells sorted by descending height
    struct Cell { int h, id; };
    vector<Cell> cells;
    cells.reserve((long long)M * N);
    for (int id = 0; id < M * N; id++) {
        cells.push_back({hgt[id], id});
    }
    sort(cells.begin(), cells.end(), [](const Cell &a, const Cell &b) {
        if (a.h != b.h) return a.h > b.h;
        return a.id < b.id;
    });

    // DP to count downhill paths from (0,0) to (M-1,N-1)
    vector<__int128> dp((long long)M * N, 0);
    dp[0] = 1;
    const int dx[4] = {-1,1,0,0};
    const int dy[4] = {0,0,-1,1};

    for (auto &c : cells) {
        int id = c.id;
        if (dp[id] == 0) continue;
        int x = id / N, y = id % N;
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx < 0 || nx >= M || ny < 0 || ny >= N) continue;
            int nid = nx * N + ny;
            if (hgt[nid] < c.h) {
                dp[nid] += dp[id];
            }
        }
    }

    __int128 answer = dp[(M-1)*N + (N-1)];
    ensuref(answer <= (__int128)1000000000,
            "Number of downhill paths exceeds 1e9");

    inf.readEof();
    return 0;
}
