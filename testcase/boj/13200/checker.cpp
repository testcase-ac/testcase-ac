#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    int T = inf.readInt();
    for (int tc = 1; tc <= T; tc++) {
        int N = inf.readInt();
        vector<vector<int>> R(N, vector<int>(N));
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                R[i][j] = inf.readInt();
        // Read participant's placement: 0 or 1 in each cell
        vector<vector<int>> P(N, vector<int>(N));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                P[i][j] = ouf.readInt(0, 1,
                    format("test %d, cell (%d,%d)", tc, i+1, j+1).c_str());
            }
        }
        // 1) Black cells must not have bulbs
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (R[i][j] != -2 && P[i][j] != 0) {
                    ouf.quitf(_wa, "test %d, cell (%d,%d) is black but has a bulb",
                              tc, i+1, j+1);
                }
            }
        }
        // 2) Numbered black cells must have exactly that many adjacent bulbs
        const int dx4[4] = {1,-1,0,0};
        const int dy4[4] = {0,0,1,-1};
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (R[i][j] >= 0 && R[i][j] <= 4) {
                    int need = R[i][j];
                    int have = 0;
                    for (int d = 0; d < 4; d++) {
                        int ni = i + dx4[d], nj = j + dy4[d];
                        if (ni >= 0 && ni < N && nj >= 0 && nj < N) {
                            have += P[ni][nj];
                        }
                    }
                    if (have != need) {
                        ouf.quitf(_wa,
                          "test %d, cell (%d,%d) requires %d adjacent bulbs, found %d",
                          tc, i+1, j+1, need, have);
                    }
                }
            }
        }
        // 3) No two bulbs may see each other in row/col without a black cell between
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) if (P[i][j] == 1) {
                for (int d = 0; d < 4; d++) {
                    int ni = i + dx4[d], nj = j + dy4[d];
                    while (ni >= 0 && ni < N && nj >= 0 && nj < N && R[ni][nj] == -2) {
                        if (P[ni][nj] == 1) {
                            ouf.quitf(_wa,
                              "test %d, bulbs at (%d,%d) and (%d,%d) see each other",
                              tc, i+1, j+1, ni+1, nj+1);
                        }
                        ni += dx4[d];
                        nj += dy4[d];
                    }
                }
            }
        }
        // 4) Every white cell must be illuminated by at least one bulb
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) if (R[i][j] == -2 && P[i][j] == 0) {
                bool lit = false;
                // Check four directions
                for (int d = 0; d < 4 && !lit; d++) {
                    int ni = i + dx4[d], nj = j + dy4[d];
                    while (ni >= 0 && ni < N && nj >= 0 && nj < N && R[ni][nj] == -2) {
                        if (P[ni][nj] == 1) {
                            lit = true;
                            break;
                        }
                        ni += dx4[d];
                        nj += dy4[d];
                    }
                }
                if (!lit) {
                    ouf.quitf(_wa,
                      "test %d, cell (%d,%d) is not illuminated by any bulb",
                      tc, i+1, j+1);
                }
            }
        }
    }
    quitf(_ok, "All tests passed");
    return 0;
}
