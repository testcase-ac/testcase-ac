#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(1, 100, "m");
    inf.readSpace();
    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    vector<string> image(m);
    for (int i = 0; i < m; ++i) {
        image[i] = inf.readToken("[.#]{1,100}", "row");
        ensuref((int)image[i].size() == n,
                "row %d has length %d, expected %d", i + 1,
                (int)image[i].size(), n);
        inf.readEoln();
    }

    const int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            if (image[r][c] != '#') {
                continue;
            }

            int black_neighbors = 0;
            for (int d = 0; d < 8; ++d) {
                int nr = r + dr[d];
                int nc = c + dc[d];
                if (0 <= nr && nr < m && 0 <= nc && nc < n &&
                    image[nr][nc] == '#') {
                    ++black_neighbors;
                }
            }

            ensuref(black_neighbors == 2,
                    "black pixel at row %d column %d has %d black neighbors",
                    r + 1, c + 1, black_neighbors);
        }
    }

    inf.readEof();
    return 0;
}
