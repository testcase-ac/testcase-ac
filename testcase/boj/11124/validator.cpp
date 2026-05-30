#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

namespace {

const int kPrintToInternal[24] = {
    0, 1, 3, 2, 4, 5, 8, 9, 12, 13, 16, 17,
    7, 6, 11, 10, 15, 14, 19, 18, 20, 21, 23, 22
};

const int kCorners[8][3] = {
    {2, 5, 8},
    {1, 9, 12},
    {0, 13, 16},
    {3, 17, 4},
    {21, 11, 6},
    {22, 15, 10},
    {23, 19, 14},
    {20, 7, 18},
};

bool isColor(char c) {
    return c == 'G' || c == 'R' || c == 'O' ||
           c == 'B' || c == 'Y' || c == 'W';
}

vector<string> splitMiddleLine(const string& line) {
    vector<string> parts;
    string cur;
    for (char ch : line) {
        if (ch == ' ') {
            parts.push_back(cur);
            cur.clear();
        } else {
            cur.push_back(ch);
        }
    }
    parts.push_back(cur);
    return parts;
}

bool sameColorSet(const array<int, 3>& a, const array<int, 3>& b) {
    array<int, 3> x = a;
    array<int, 3> y = b;
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    return x == y;
}

int rotationOffset(const array<int, 3>& observed, const array<int, 3>& target) {
    for (int offset = 0; offset < 3; ++offset) {
        bool ok = true;
        for (int i = 0; i < 3; ++i) {
            if (observed[i] != target[(i + offset) % 3]) {
                ok = false;
                break;
            }
        }
        if (ok) return offset;
    }
    return -1;
}

int findOppositeFaceColor(const array<int, 24>& cube, int a, int b) {
    for (int i = 1; i < 8; ++i) {
        bool hasA = false;
        bool hasB = false;
        for (int j = 0; j < 3; ++j) {
            int color = cube[kCorners[i][j]];
            hasA = hasA || color == a;
            hasB = hasB || color == b;
        }
        if (!hasA || !hasB) continue;

        for (int j = 0; j < 3; ++j) {
            int color = cube[kCorners[i][j]];
            if (color != a && color != b) return color;
        }
    }
    return -1;
}

void ensureReachableCubeState(const array<int, 24>& cube, int tc) {
    array<int, 6> faceColor = {
        cube[2],
        cube[5],
        cube[8],
        findOppositeFaceColor(cube, cube[2], cube[8]),
        findOppositeFaceColor(cube, cube[5], cube[2]),
        findOppositeFaceColor(cube, cube[8], cube[5]),
    };

    set<int> distinctFaces(faceColor.begin(), faceColor.end());
    ensuref(!distinctFaces.count(-1) && (int)distinctFaces.size() == 6,
            "test case %d: cube corner color relationships cannot form six solved faces", tc);

    array<array<int, 3>, 8> targetCorners;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 3; ++j) {
            targetCorners[i][j] = faceColor[kCorners[i][j] / 4];
        }
    }

    vector<int> used(8, 0);
    int orientationSum = 0;
    for (int pos = 0; pos < 8; ++pos) {
        array<int, 3> observed = {
            cube[kCorners[pos][0]],
            cube[kCorners[pos][1]],
            cube[kCorners[pos][2]],
        };

        int cubie = -1;
        for (int i = 0; i < 8; ++i) {
            if (sameColorSet(observed, targetCorners[i])) {
                cubie = i;
                break;
            }
        }

        ensuref(cubie != -1, "test case %d: corner %d is not a valid solved-cube corner",
                tc, pos + 1);
        ensuref(!used[cubie], "test case %d: corner cubie %d appears more than once",
                tc, cubie + 1);
        used[cubie] = 1;

        int orientation = rotationOffset(observed, targetCorners[cubie]);
        ensuref(orientation != -1, "test case %d: corner %d has invalid sticker orientation",
                tc, pos + 1);
        orientationSum += orientation;
    }

    ensuref(orientationSum % 3 == 0,
            "test case %d: corner orientations are not reachable from a solved cube", tc);
}

void appendTopBottomLine(array<int, 24>& cube, int& printedIndex, const char* name, int tc) {
    string line = inf.readToken("[GROBYW]{2}", name);
    inf.readEoln();
    ensuref((int)line.size() == 2, "test case %d: %s must have exactly two stickers",
            tc, name);
    for (char c : line) {
        ensuref(isColor(c), "test case %d: invalid color '%c' in %s", tc, c, name);
        cube[kPrintToInternal[printedIndex++]] = c;
    }
}

void appendMiddleLine(array<int, 24>& cube, int& printedIndex, const char* name, int tc) {
    string line = inf.readLine("[GROBYW]{2}\\ [GROBYW]{2}\\ [GROBYW]{2}\\ [GROBYW]{2}", name);
    vector<string> parts = splitMiddleLine(line);
    ensuref((int)parts.size() == 4, "test case %d: %s must have four sticker pairs",
            tc, name);
    for (const string& part : parts) {
        ensuref((int)part.size() == 2, "test case %d: %s contains a malformed sticker pair",
                tc, name);
        for (char c : part) {
            ensuref(isColor(c), "test case %d: invalid color '%c' in %s", tc, c, name);
            cube[kPrintToInternal[printedIndex++]] = c;
        }
    }
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        array<int, 24> cube{};
        int printedIndex = 0;

        appendTopBottomLine(cube, printedIndex, "top_line_1", tc);
        appendTopBottomLine(cube, printedIndex, "top_line_2", tc);
        appendMiddleLine(cube, printedIndex, "middle_line_1", tc);
        appendMiddleLine(cube, printedIndex, "middle_line_2", tc);
        appendTopBottomLine(cube, printedIndex, "bottom_line_1", tc);
        appendTopBottomLine(cube, printedIndex, "bottom_line_2", tc);
        ensuref(printedIndex == 24, "test case %d: expected 24 stickers, got %d",
                tc, printedIndex);

        map<int, int> colorCount;
        for (int color : cube) colorCount[color]++;
        ensuref((int)colorCount.size() == 6,
                "test case %d: there must be exactly six distinct colors", tc);
        for (const auto& [color, count] : colorCount) {
            ensuref(count == 4, "test case %d: color '%c' appears %d times, expected 4",
                    tc, color, count);
        }

        ensureReachableCubeState(cube, tc);

        if (tc < T) {
            string emptyLine = inf.readLine("[^]*", "empty_line");
            ensuref(emptyLine.empty(), "test case %d: expected an empty line after cube", tc);
        } else if (!inf.eof()) {
            string emptyLine = inf.readLine("[^]*", "final_empty_line");
            ensuref(emptyLine.empty(),
                    "test case %d: expected only an optional empty line after final cube", tc);
        }
    }

    inf.readEof();
}
