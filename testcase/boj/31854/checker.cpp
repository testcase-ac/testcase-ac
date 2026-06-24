#include "testlib.h"

#include <vector>

using namespace std;

int n;
vector<vector<char>> horizontalSigns;
vector<vector<char>> verticalSigns;

struct Answer {
    vector<vector<int>> grid;
};

Answer readAnswer(InStream& stream) {
    const int maxValue = n * n;
    vector<vector<int>> grid(n, vector<int>(n));
    vector<char> seen(maxValue + 1, 0);

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            int value = stream.readInt(1, maxValue, format("A[%d][%d]", r + 1, c + 1).c_str());
            if (seen[value]) {
                stream.quitf(_wa, "value %d appears more than once", value);
            }
            seen[value] = 1;
            grid[r][c] = value;
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after grid");
    }

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c + 1 < n; ++c) {
            char sign = horizontalSigns[r][c];
            int left = grid[r][c];
            int right = grid[r][c + 1];
            if (sign == '>' && !(left > right)) {
                stream.quitf(_wa,
                             "horizontal inequality at row %d column %d requires %d > %d",
                             r + 1, c + 1, left, right);
            }
            if (sign == '<' && !(left < right)) {
                stream.quitf(_wa,
                             "horizontal inequality at row %d column %d requires %d < %d",
                             r + 1, c + 1, left, right);
            }
        }
    }

    for (int r = 0; r + 1 < n; ++r) {
        for (int c = 0; c < n; ++c) {
            char sign = verticalSigns[r][c];
            int upper = grid[r][c];
            int lower = grid[r + 1][c];
            if (sign == '>' && !(upper > lower)) {
                stream.quitf(_wa,
                             "vertical inequality at row %d column %d requires %d > %d",
                             r + 1, c + 1, upper, lower);
            }
            if (sign == '<' && !(upper < lower)) {
                stream.quitf(_wa,
                             "vertical inequality at row %d column %d requires %d < %d",
                             r + 1, c + 1, upper, lower);
            }
        }
    }

    return {grid};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    horizontalSigns.assign(n, vector<char>(n - 1));
    verticalSigns.assign(n - 1, vector<char>(n));

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c + 1 < n; ++c) {
            horizontalSigns[r][c] = inf.readToken("[<>]")[0];
        }
    }

    for (int r = 0; r + 1 < n; ++r) {
        for (int c = 0; c < n; ++c) {
            verticalSigns[r][c] = inf.readToken("[<>]")[0];
        }
    }

    readAnswer(ans);
    readAnswer(ouf);

    quitf(_ok, "valid inequality puzzle solution");
}
