#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

struct Cell {
    long long value;
    int row;
    int col;
};

struct Answer {
    bool impossible;
};

int n, m;
long long k;

bool isIntegerToken(const string& token) {
    if (token.empty()) {
        return false;
    }
    int pos = 0;
    if (token[0] == '-') {
        pos = 1;
        if ((int)token.size() == 1) {
            return false;
        }
    }
    for (int i = pos; i < (int)token.size(); ++i) {
        if (token[i] < '0' || token[i] > '9') {
            return false;
        }
    }
    return true;
}

long long parseInteger(InStream& stream, const string& token, long long minValue, long long maxValue,
                       const string& name) {
    if (!isIntegerToken(token)) {
        stream.quitf(_wa, "%s is not an integer: %s", name.c_str(), token.c_str());
    }

    bool negative = token[0] == '-';
    int pos = negative ? 1 : 0;
    __int128 value = 0;
    for (int i = pos; i < (int)token.size(); ++i) {
        value = value * 10 + (token[i] - '0');
        if (value > (__int128)1000000000000000000LL + 1) {
            stream.quitf(_wa, "%s is outside allowed range: %s", name.c_str(), token.c_str());
        }
    }
    if (negative) {
        value = -value;
    }
    if (value < minValue || value > maxValue) {
        stream.quitf(_wa, "%s is outside allowed range [%lld, %lld]: %s", name.c_str(), minValue,
                     maxValue, token.c_str());
    }
    return (long long)value;
}

bool adjacent(const Cell& a, const Cell& b) {
    return abs(a.row - b.row) + abs(a.col - b.col) == 1;
}

void validateGrid(InStream& stream, vector<vector<long long>>& grid, vector<Cell>& cells) {
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            long long value = grid[r][c];
            if (r > 0 && llabs(value - grid[r - 1][c]) > k) {
                stream.quitf(_wa, "adjacent cells (%d,%d) and (%d,%d) differ by more than K", r + 1,
                             c + 1, r, c + 1);
            }
            if (c > 0 && llabs(value - grid[r][c - 1]) > k) {
                stream.quitf(_wa, "adjacent cells (%d,%d) and (%d,%d) differ by more than K", r + 1,
                             c + 1, r + 1, c);
            }
        }
    }

    sort(cells.begin(), cells.end(), [](const Cell& a, const Cell& b) {
        if (a.value != b.value) {
            return a.value < b.value;
        }
        if (a.row != b.row) {
            return a.row < b.row;
        }
        return a.col < b.col;
    });

    for (int i = 0; i < (int)cells.size(); ++i) {
        for (int j = i + 1; j < (int)cells.size() && cells[j].value - cells[i].value <= k; ++j) {
            if (!adjacent(cells[i], cells[j])) {
                stream.quitf(_wa,
                             "non-adjacent cells (%d,%d) and (%d,%d) have humidity difference %lld, "
                             "which is not greater than K",
                             cells[i].row + 1, cells[i].col + 1, cells[j].row + 1, cells[j].col + 1,
                             cells[j].value - cells[i].value);
            }
        }
    }
}

Answer readAnswer(InStream& stream) {
    string first = stream.readToken("[+-]?[0-9]+", "first output token");
    long long firstValue = parseInteger(stream, first, -1, 1000000000000000000LL, "first output token");

    if (firstValue == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true};
    }

    vector<vector<long long>> grid(n, vector<long long>(m));
    vector<Cell> cells;
    cells.reserve((size_t)n * (size_t)m);

    grid[0][0] = firstValue;
    cells.push_back({firstValue, 0, 0});
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (r == 0 && c == 0) {
                continue;
            }
            string token = stream.readToken("[+-]?[0-9]+", format("humidity[%d][%d]", r + 1, c + 1).c_str());
            long long value = parseInteger(stream, token, 0, 1000000000000000000LL,
                                           format("humidity[%d][%d]", r + 1, c + 1).c_str());
            grid[r][c] = value;
            cells.push_back({value, r, c});
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after grid");
    }

    validateGrid(stream, grid, cells);
    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    k = inf.readLong();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail, "participant provided a valid construction while jury says impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant says impossible, but jury provides a valid construction");
    }

    quitf(_ok, "valid construction");
}
