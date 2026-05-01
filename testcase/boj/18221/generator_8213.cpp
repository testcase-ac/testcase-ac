#include "testlib.h"
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Grid size
    int N = rnd.next(7, 12);
    // Position relation: 0 = same row, 1 = same col, 2 = neither
    int posType = rnd.next(0, 2);
    int r1, c1, r2, c2;
    if (posType == 0) {
        // same row
        r1 = rnd.next(1, N);
        r2 = r1;
        c1 = rnd.next(1, N);
        do { c2 = rnd.next(1, N); } while (c2 == c1);
    } else if (posType == 1) {
        // same column
        c1 = rnd.next(1, N);
        c2 = c1;
        r1 = rnd.next(1, N);
        do { r2 = rnd.next(1, N); } while (r2 == r1);
    } else {
        // neither same row nor same column
        r1 = rnd.next(1, N);
        c1 = rnd.next(1, N);
        do {
            r2 = rnd.next(1, N);
            c2 = rnd.next(1, N);
        } while (r2 == r1 || c2 == c1);
    }
    // Initialize grid
    vector<vector<int>> grid(N, vector<int>(N, 0));
    grid[r1-1][c1-1] = 2; // Seonggyu
    grid[r2-1][c2-1] = 5; // Professor
    // Hyper-parameter for number of other students
    int maxStu = int(0.3 * N * N);
    if (maxStu < 0) maxStu = 0;
    // t = -1 small, 0 uniform, 1 large
    vector<int> tvals = {-1, 0, 1};
    int t = rnd.any(tvals);
    int K = rnd.wnext(maxStu + 1, t); // in [0, maxStu]
    // Collect available cells
    vector<pair<int,int>> avail;
    avail.reserve(N*N);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if ((i==r1 && j==c1) || (i==r2 && j==c2)) continue;
            avail.emplace_back(i-1, j-1);
        }
    }
    shuffle(avail.begin(), avail.end());
    for (int i = 0; i < K && i < (int)avail.size(); i++) {
        auto p = avail[i];
        grid[p.first][p.second] = 1;
    }
    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d%c", grid[i][j], j+1==N?'\n':' ');
        }
    }
    return 0;
}
