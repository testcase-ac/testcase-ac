#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(5, 100, "N");
    inf.readSpace();
    int M = inf.readInt(5, 100, "M");
    inf.readEoln();

    vector<string> g(N);
    for (int i = 0; i < N; ++i) {
        g[i] = inf.readToken("[#.]{1,100}", "row");
        inf.readEoln();
        ensuref((int)g[i].size() == M, "Row %d length is %d, expected %d", i + 1, (int)g[i].size(), M);
    }

    // Validate exactly one square border as described.

    // Collect all '#' positions.
    vector<pair<int,int>> cells;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            if (g[i][j] == '#')
                cells.push_back({i, j});

    ensuref(!cells.empty(), "There must be at least one painted cell");

    // Find bounding box of all '#'
    int minR = N, maxR = -1, minC = M, maxC = -1;
    for (auto [r, c] : cells) {
        minR = min(minR, r);
        maxR = max(maxR, r);
        minC = min(minC, c);
        maxC = max(maxC, c);
    }

    int h = maxR - minR + 1;
    int w = maxC - minC + 1;
    ensuref(h == w, "Bounding box is not a square: height=%d width=%d", h, w);

    int L = h;
    ensuref(L >= 5 && (L % 2 == 1), "Square side length must be odd and > 3, got %d", L);

    // Build ideal square border mask (without missing edge)
    vector<vector<int>> border(N, vector<int>(M, 0));
    for (int i = 0; i < L; ++i) {
        border[minR][minC + i] = 1;
        border[maxR][minC + i] = 1;
        border[minR + i][minC] = 1;
        border[minR + i][maxC] = 1;
    }

    // Count border cells and check all '#' are within border.
    int totalBorder = 0;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            if (border[i][j])
                ++totalBorder;

    // Each side length is L, total perimeter cells = 4*L - 4 (corners counted twice)
    int expectedBorder = 4 * L - 4;
    ensuref(totalBorder == expectedBorder,
            "Internal error: computed border cells %d, expected %d", totalBorder, expectedBorder);

    // One whole side's cells except center must be '#', and all other border cells must be '#'
    // while exactly one side's center is '.'
    int missingSide = -1; // 0=TOP,1=RIGHT,2=BOTTOM,3=LEFT
    int centerIdx = L / 2;

    auto checkSide = [&](int side) -> bool {
        // Returns true if this side is candidate for missing-middle (center is '.', others '#')
        for (int k = 0; k < L; ++k) {
            int r, c;
            if (side == 0) { // top
                r = minR; c = minC + k;
            } else if (side == 1) { // right
                r = minR + k; c = maxC;
            } else if (side == 2) { // bottom
                r = maxR; c = minC + k;
            } else { // left
                r = minR + k; c = minC;
            }
            if (k == centerIdx) {
                if (g[r][c] != '.') return false;
            } else {
                if (g[r][c] != '#') return false;
            }
        }
        return true;
    };

    // First ensure all non-center border cells are '#', and all centers are either '#' or '.'
    // and non-border '#' do not exist.
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            if (g[i][j] == '#')
                ensuref(border[i][j], "Painted cell at (%d,%d) is not on the square border", i + 1, j + 1);

    // Determine which side is missing middle.
    int cntMissingSides = 0;
    for (int side = 0; side < 4; ++side) {
        if (checkSide(side)) {
            missingSide = side;
            ++cntMissingSides;
        }
    }
    ensuref(cntMissingSides == 1, "There must be exactly one side with missing center, found %d", cntMissingSides);

    // Also ensure that all other border cells are '#'.
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            if (border[i][j]) {
                bool isCenterOfMissingSide = false;
                int r = i, c = j;
                if (missingSide == 0 && r == minR && c == minC + centerIdx) isCenterOfMissingSide = true;
                if (missingSide == 1 && c == maxC && r == minR + centerIdx) isCenterOfMissingSide = true;
                if (missingSide == 2 && r == maxR && c == minC + centerIdx) isCenterOfMissingSide = true;
                if (missingSide == 3 && c == minC && r == minR + centerIdx) isCenterOfMissingSide = true;

                if (!isCenterOfMissingSide)
                    ensuref(g[i][j] == '#', "Border cell at (%d,%d) must be painted", i + 1, j + 1);
            }

    inf.readEof();
}
