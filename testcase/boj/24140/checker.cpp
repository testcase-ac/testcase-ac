#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Claim {
    vector<int> order;
    vector<int> position;
};

int n, w, h;
vector<vector<int>> grid;
vector<int> minRow, maxRow, minCol, maxCol;

Claim readClaim(InStream& stream) {
    Claim claim;
    claim.order.resize(n);
    claim.position.assign(n + 1, -1);

    for (int i = 0; i < n; ++i) {
        int color = stream.readInt(1, n, format("order[%d]", i + 1).c_str());
        if (claim.position[color] != -1) {
            stream.quitf(_wa, "color %d appears more than once", color);
        }
        claim.order[i] = color;
        claim.position[color] = i;
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after the order");
    }

    for (int color = 1; color <= n; ++color) {
        if (minRow[color] == h) {
            continue;
        }
        for (int r = minRow[color]; r <= maxRow[color]; ++r) {
            for (int c = minCol[color]; c <= maxCol[color]; ++c) {
                int visible = grid[r][c];
                if (visible == 0 || visible == color) {
                    continue;
                }
                if (claim.position[color] >= claim.position[visible]) {
                    stream.quitf(_wa,
                                 "color %d must be placed before visible color %d at row %d column %d",
                                 color, visible, r + 1, c + 1);
                }
            }
        }
    }

    return claim;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 1000, "N");
    w = inf.readInt(1, 100, "W");
    h = inf.readInt(1, 100, "H");

    grid.assign(h, vector<int>(w));
    minRow.assign(n + 1, h);
    maxRow.assign(n + 1, -1);
    minCol.assign(n + 1, w);
    maxCol.assign(n + 1, -1);

    for (int r = 0; r < h; ++r) {
        for (int c = 0; c < w; ++c) {
            int color = inf.readInt(0, n, format("C[%d][%d]", r + 1, c + 1).c_str());
            grid[r][c] = color;
            if (color != 0) {
                minRow[color] = min(minRow[color], r);
                maxRow[color] = max(maxRow[color], r);
                minCol[color] = min(minCol[color], c);
                maxCol[color] = max(maxCol[color], c);
            }
        }
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    quitf(_ok, "valid order with %d colors", n);
}
