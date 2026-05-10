#include "testlib.h"
#include <vector>
#include <string>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int case_no = 0;
    while (true) {
        // Read m and n
        int m = inf.readInt(0, 100, "m");
        inf.readSpace();
        int n = inf.readInt(0, 100, "n");
        inf.readEoln();

        // Termination condition
        if (m == 0) {
            ensuref(n == 0, "When m = 0 (termination), n must also be 0; found n = %d", n);
            break;
        }

        // Count test cases
        case_no++;
        ensuref(case_no <= 100000, "Number of test cases exceeds the limit of 100000: %d", case_no);
        setTestCase(case_no);

        // Validate dimensions
        ensuref(m >= 1 && m <= 100, "m must be between 1 and 100; found %d", m);
        ensuref(n >= 1 && n <= 100, "n must be between 1 and 100; found %d", n);

        // Read the grid
        vector<string> grid(m);
        string regex = "[*@]{" + to_string(n) + "," + to_string(n) + "}";
        for (int i = 0; i < m; i++) {
            grid[i] = inf.readLine(regex.c_str(), "row");
        }

        // Check global property: each connected component (8-dir) of '@' has size <= 100
        vector<vector<bool>> seen(m, vector<bool>(n, false));
        int dx[8] = { -1,-1,-1, 0, 0, 1, 1, 1 };
        int dy[8] = { -1, 0, 1,-1, 1,-1, 0, 1 };
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '@' && !seen[i][j]) {
                    // BFS/DFS this component
                    int cnt = 0;
                    vector<pair<int,int>> stk;
                    stk.reserve(128);
                    seen[i][j] = true;
                    stk.emplace_back(i, j);
                    while (!stk.empty()) {
                        auto [x, y] = stk.back();
                        stk.pop_back();
                        cnt++;
                        for (int d = 0; d < 8; d++) {
                            int nx = x + dx[d];
                            int ny = y + dy[d];
                            if (nx >= 0 && nx < m && ny >= 0 && ny < n
                                && grid[nx][ny] == '@'
                                && !seen[nx][ny]) {
                                seen[nx][ny] = true;
                                stk.emplace_back(nx, ny);
                            }
                        }
                    }
                    ensuref(cnt <= 100,
                            "Oil deposit too large: found %d pockets (maximum allowed is 100) in component starting at (%d, %d)",
                            cnt, i, j);
                }
            }
        }
    }

    inf.readEof();
    return 0;
}
