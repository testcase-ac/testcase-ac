#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small maze dimensions
    int N = rnd.next(2, 10);
    int M = rnd.next(2, 10);
    // Density for extra corridors
    double density = rnd.next(0.0, 1.0);

    // Prepare grid, 0 = wall, 1 = passage
    vector<vector<int>> grid(N, vector<int>(M, 0));

    // Create a random monotonic path from (0,0) to (N-1,M-1)
    vector<char> dirs;
    for (int i = 0; i < M - 1; i++) dirs.push_back('R');
    for (int i = 0; i < N - 1; i++) dirs.push_back('D');
    shuffle(dirs.begin(), dirs.end());
    int r = 0, c = 0;
    grid[r][c] = 1;
    for (char d : dirs) {
        if (d == 'R') c++;
        else r++;
        grid[r][c] = 1;
    }

    // Fill other cells randomly
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (grid[i][j] == 0) {
                grid[i][j] = (rnd.next() < density ? 1 : 0);
            }
        }
    }
    // Ensure start and end are open
    grid[0][0] = 1;
    grid[N-1][M-1] = 1;

    // Output
    println(N, M);
    for (int i = 0; i < N; i++) {
        string s;
        for (int j = 0; j < M; j++)
            s.push_back(char('0' + grid[i][j]));
        println(s);
    }
    return 0;
}
