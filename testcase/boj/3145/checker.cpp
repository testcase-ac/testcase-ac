#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

struct NameSpan {
    int row;
    int left;
    int right;
};

struct Claim {
    int row;
    int col;
    string name;

    bool operator<(const Claim& other) const {
        return tie(row, col, name) < tie(other.row, other.col, other.name);
    }

    bool operator==(const Claim& other) const {
        return row == other.row && col == other.col && name == other.name;
    }
};

int r, c;
vector<string> board;
map<string, NameSpan> nameSpans;
set<pair<int, int>> towns;

bool adjacentToName(int townRow, int townCol, const NameSpan& span) {
    if (abs(townRow - span.row) > 1) {
        return false;
    }
    int nearestCol = min(max(townCol, span.left), span.right);
    return abs(townCol - nearestCol) <= 1;
}

set<Claim> readClaims(InStream& stream) {
    set<Claim> claims;
    set<pair<int, int>> usedTowns;
    set<string> usedNames;

    for (int line = 1; !stream.seekEof(); ++line) {
        int row = stream.readInt(1, r, format("row on output line %d", line).c_str());
        int col = stream.readInt(1, c, format("column on output line %d", line).c_str());
        string name = stream.readToken("[A-Z]+", format("name on output line %d", line).c_str());
        stream.readEoln();

        int zeroRow = row - 1;
        int zeroCol = col - 1;
        if (!towns.count({zeroRow, zeroCol})) {
            stream.quitf(_wa, "line %d points to (%d, %d), which is not a town", line, row, col);
        }
        if (!usedTowns.insert({zeroRow, zeroCol}).second) {
            stream.quitf(_wa, "town (%d, %d) is listed more than once", row, col);
        }

        auto it = nameSpans.find(name);
        if (it == nameSpans.end()) {
            stream.quitf(_wa, "line %d uses name '%s', which is not a map name", line, name.c_str());
        }
        if (!usedNames.insert(name).second) {
            stream.quitf(_wa, "name '%s' is listed more than once", name.c_str());
        }
        if (!adjacentToName(zeroRow, zeroCol, it->second)) {
            stream.quitf(_wa, "town (%d, %d) is not adjacent to name '%s'", row, col, name.c_str());
        }

        claims.insert({zeroRow, zeroCol, name});
    }

    if ((int)claims.size() != (int)towns.size()) {
        stream.quitf(_wa, "expected %d town claims, found %d", (int)towns.size(), (int)claims.size());
    }
    if ((int)claims.size() != (int)nameSpans.size()) {
        stream.quitf(_wa, "expected %d name claims, found %d", (int)nameSpans.size(), (int)claims.size());
    }

    return claims;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    r = inf.readInt();
    c = inf.readInt();
    board.resize(r);
    for (int i = 0; i < r; ++i) {
        board[i] = inf.readToken();
        for (int j = 0; j < c; ++j) {
            if (board[i][j] == 'x') {
                towns.insert({i, j});
            }
        }
    }

    for (int i = 0; i < r; ++i) {
        int j = 0;
        while (j < c) {
            if (!isupper((unsigned char)board[i][j])) {
                ++j;
                continue;
            }
            int left = j;
            string name;
            while (j < c && isupper((unsigned char)board[i][j])) {
                name.push_back(board[i][j]);
                ++j;
            }
            nameSpans[name] = {i, left, j - 1};
        }
    }

    set<Claim> jury = readClaims(ans);
    set<Claim> participant = readClaims(ouf);

    if (participant != jury) {
        quitf(_wa, "participant claims do not match jury baseline");
    }
    quitf(_ok, "accepted %d town claims", (int)participant.size());
}
