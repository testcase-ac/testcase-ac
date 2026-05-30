#include "testlib.h"
#include <algorithm>
#include <array>
#include <string>
#include <vector>
using namespace std;

struct Sticker {
    int face;
    int row;
    int col;
};

static const string faceColors = "WORBGY";
static const string cubieColors = "WORBGY";
enum { L = 0, D = 1, Ba = 2, U = 3, F = 4, R = 5 };

static char at(const array<array<array<char, 3>, 3>, 6>& cube, Sticker s) {
    return cube[s.face][s.row][s.col];
}

static int colorId(char c) {
    size_t p = cubieColors.find(c);
    ensuref(p != string::npos, "internal color mapping is missing color '%c'", c);
    return (int)p;
}

static int permutationParity(const vector<int>& permutation) {
    int inversions = 0;
    for (int i = 0; i < (int)permutation.size(); ++i) {
        for (int j = i + 1; j < (int)permutation.size(); ++j) {
            inversions ^= permutation[i] > permutation[j];
        }
    }
    return inversions;
}

static int cornerOrientation(const array<char, 3>& colors) {
    for (int i = 0; i < 3; ++i) {
        if (colors[i] == 'B' || colors[i] == 'O') {
            return i;
        }
    }
    ensuref(false, "corner has no U/D color");
    return 0;
}

static int edgeOrientation(const array<char, 2>& colors, const array<int, 2>& faces) {
    for (int i = 0; i < 2; ++i) {
        if (colors[i] == 'B' || colors[i] == 'O') {
            return (faces[i] == U || faces[i] == D) ? 0 : 1;
        }
    }
    for (int i = 0; i < 2; ++i) {
        if (colors[i] == 'G' || colors[i] == 'R') {
            return (faces[i] == F || faces[i] == Ba) ? 0 : 1;
        }
    }
    ensuref(false, "edge has no orientation color");
    return 0;
}

static int findCubie(const vector<vector<int>>& sortedCubies, vector<int> colors) {
    sort(colors.begin(), colors.end());
    for (int i = 0; i < (int)sortedCubies.size(); ++i) {
        if (sortedCubies[i] == colors) {
            return i;
        }
    }
    return -1;
}

static void validateReachableCube(const array<array<array<char, 3>, 3>, 6>& cube, int tc) {
    static const array<array<Sticker, 3>, 8> cornerStickers = {{
        {{{U, 2, 2}, {R, 0, 0}, {F, 0, 2}}},
        {{{U, 2, 0}, {F, 0, 0}, {L, 0, 2}}},
        {{{U, 0, 0}, {L, 0, 0}, {Ba, 0, 2}}},
        {{{U, 0, 2}, {Ba, 0, 0}, {R, 0, 2}}},
        {{{D, 0, 2}, {F, 2, 2}, {R, 2, 0}}},
        {{{D, 0, 0}, {L, 2, 2}, {F, 2, 0}}},
        {{{D, 2, 0}, {Ba, 2, 2}, {L, 2, 0}}},
        {{{D, 2, 2}, {R, 2, 2}, {Ba, 2, 0}}},
    }};
    static const array<array<Sticker, 2>, 12> edgeStickers = {{
        {{{U, 1, 2}, {R, 0, 1}}},
        {{{U, 2, 1}, {F, 0, 1}}},
        {{{U, 1, 0}, {L, 0, 1}}},
        {{{U, 0, 1}, {Ba, 0, 1}}},
        {{{D, 1, 2}, {R, 2, 1}}},
        {{{D, 0, 1}, {F, 2, 1}}},
        {{{D, 1, 0}, {L, 2, 1}}},
        {{{D, 2, 1}, {Ba, 2, 1}}},
        {{{F, 1, 2}, {R, 1, 0}}},
        {{{F, 1, 0}, {L, 1, 2}}},
        {{{Ba, 1, 2}, {L, 1, 0}}},
        {{{Ba, 1, 0}, {R, 1, 2}}},
    }};

    vector<vector<int>> cornerCubies;
    for (const auto& cubie : cornerStickers) {
        vector<int> colors;
        for (Sticker s : cubie) colors.push_back(colorId(cubieColors[s.face]));
        sort(colors.begin(), colors.end());
        cornerCubies.push_back(colors);
    }
    vector<vector<int>> edgeCubies;
    for (const auto& cubie : edgeStickers) {
        vector<int> colors;
        for (Sticker s : cubie) colors.push_back(colorId(cubieColors[s.face]));
        sort(colors.begin(), colors.end());
        edgeCubies.push_back(colors);
    }

    vector<int> cornerPermutation;
    vector<int> edgePermutation;
    vector<bool> seenCorners(8, false);
    vector<bool> seenEdges(12, false);
    int cornerTwistSum = 0;
    int edgeFlipSum = 0;

    for (int i = 0; i < 8; ++i) {
        array<char, 3> colors{};
        vector<int> ids;
        for (int j = 0; j < 3; ++j) {
            colors[j] = at(cube, cornerStickers[i][j]);
            ids.push_back(colorId(colors[j]));
        }
        int cubie = findCubie(cornerCubies, ids);
        ensuref(cubie != -1, "Case %d: corner position %d has invalid color combination", tc, i + 1);
        ensuref(!seenCorners[cubie], "Case %d: duplicate corner cubie at position %d", tc, i + 1);
        seenCorners[cubie] = true;
        cornerPermutation.push_back(cubie);
        cornerTwistSum = (cornerTwistSum + cornerOrientation(colors)) % 3;
    }
    ensuref(cornerTwistSum == 0, "Case %d: corner orientations are not reachable", tc);

    for (int i = 0; i < 12; ++i) {
        array<char, 2> colors{};
        array<int, 2> faces{};
        vector<int> ids;
        for (int j = 0; j < 2; ++j) {
            colors[j] = at(cube, edgeStickers[i][j]);
            faces[j] = edgeStickers[i][j].face;
            ids.push_back(colorId(colors[j]));
        }
        int cubie = findCubie(edgeCubies, ids);
        ensuref(cubie != -1, "Case %d: edge position %d has invalid color combination", tc, i + 1);
        ensuref(!seenEdges[cubie], "Case %d: duplicate edge cubie at position %d", tc, i + 1);
        seenEdges[cubie] = true;
        edgePermutation.push_back(cubie);
        edgeFlipSum ^= edgeOrientation(colors, faces);
    }
    ensuref(edgeFlipSum == 0, "Case %d: edge orientations are not reachable", tc);
    ensuref(permutationParity(cornerPermutation) == permutationParity(edgePermutation),
            "Case %d: corner and edge permutation parity differs", tc);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 10000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        array<array<array<char, 3>, 3>, 6> cube{};
        vector<vector<char>> rows(3, vector<char>(18));
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 18; ++j) {
                char c = inf.readToken("[WORBGY]", "cube_color")[0];
                ensuref(faceColors.find(c) != string::npos,
                        "Case %d: cube row %d, token %d is '%c' (invalid color)",
                        tc, i + 1, j + 1, c);
                rows[i][j] = c;
                if (j + 1 < 18) {
                    inf.readSpace();
                } else {
                    inf.readEoln();
                }
            }
        }

        vector<int> count(6, 0);
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 18; ++j) {
                char c = rows[i][j];
                int idx = faceColors.find(c);
                count[idx]++;
            }
        }
        for (int k = 0; k < 6; ++k) {
            ensuref(count[k] == 9,
                    "Case %d: color '%c' appears %d times (expected 9)",
                    tc, faceColors[k], count[k]);
        }

        for (int f = 0; f < 6; ++f) {
            int tokenIdx = 3 * f + 1;
            char actual = rows[1][tokenIdx];
            char expected = faceColors[f];
            ensuref(actual == expected,
                    "Case %d: face %d center color is '%c' (expected '%c')",
                    tc, f + 1, actual, expected);
        }

        for (int row = 0; row < 3; ++row) {
            cube[L][0][2 - row] = rows[row][0];
            cube[L][1][2 - row] = rows[row][1];
            cube[L][2][2 - row] = rows[row][2];
            cube[D][row][0] = rows[row][3];
            cube[D][row][1] = rows[row][4];
            cube[D][row][2] = rows[row][5];
            cube[Ba][2 - row][2] = rows[row][6];
            cube[Ba][2 - row][1] = rows[row][7];
            cube[Ba][2 - row][0] = rows[row][8];
            cube[U][row][0] = rows[row][9];
            cube[U][row][1] = rows[row][10];
            cube[U][row][2] = rows[row][11];
            cube[F][row][0] = rows[row][12];
            cube[F][row][1] = rows[row][13];
            cube[F][row][2] = rows[row][14];
            cube[R][row][0] = rows[row][15];
            cube[R][row][1] = rows[row][16];
            cube[R][row][2] = rows[row][17];
        }
        validateReachableCube(cube, tc);

        inf.readToken("[WORBGY]{1,1000}", "moves");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
