#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, H
    int N = inf.readInt(2, 10, "N");
    inf.readSpace();
    // M maximum possible is (N-1)*H, but H not read yet; we know H<=30 and N<=10 so (N-1)*H<=9*30=270
    int M = inf.readInt(0, 270, "M");
    inf.readSpace();
    int H = inf.readInt(1, 30, "H");
    inf.readEoln();

    // Now fully validate M bound
    ensuref(M <= (long long)(N - 1) * H,
            "M is too large: M=%d but (N-1)*H=%d", M, (N - 1) * H);

    // Read the M horizontal lines
    vector<pair<int,int>> lines;
    lines.reserve(M);
    for (int i = 0; i < M; i++) {
        int a = inf.readInt(1, H, "a");
        inf.readSpace();
        int b = inf.readInt(1, N - 1, "b");
        inf.readEoln();
        lines.emplace_back(a, b);
    }

    // Validate no duplicates and no adjacent (touching or consecutive) lines
    // used[a][b] means there's a horizontal line at row a connecting vertical b and b+1
    vector<vector<bool>> used(H + 2, vector<bool>(N + 1, false));
    for (auto &pr : lines) {
        int a = pr.first;
        int b = pr.second;
        ensuref(!used[a][b],
                "Duplicate horizontal line at row %d, column %d", a, b);
        used[a][b] = true;
    }

    for (auto &pr : lines) {
        int a = pr.first;
        int b = pr.second;
        // Check sideways touching: same row a, columns b-1 or b+1
        if (b - 1 >= 1) {
            ensuref(!used[a][b - 1],
                    "Touching horizontal lines at (%d,%d) and (%d,%d)",
                    a, b - 1, a, b);
        }
        if (b + 1 <= N - 1) {
            ensuref(!used[a][b + 1],
                    "Touching horizontal lines at (%d,%d) and (%d,%d)",
                    a, b, a, b + 1);
        }
        // Check vertical adjacency: same column b, rows a-1 or a+1
        if (a - 1 >= 1) {
            ensuref(!used[a - 1][b],
                    "Consecutive horizontal lines at (%d,%d) and (%d,%d)",
                    a - 1, b, a, b);
        }
        if (a + 1 <= H) {
            ensuref(!used[a + 1][b],
                    "Consecutive horizontal lines at (%d,%d) and (%d,%d)",
                    a, b, a + 1, b);
        }
    }

    inf.readEof();
    return 0;
}
