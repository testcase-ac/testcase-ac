#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

struct Claim {
    bool impossible;
    int moves;
};

int r, c;
vector<string> board;
vector<pair<int, int>> turtle;
pair<int, int> home;

bool reachesHome(int dr, int dc) {
    for (auto [tr, tc] : turtle) {
        if (tr + dr == home.first && tc + dc == home.second) {
            return true;
        }
    }
    return false;
}

void validatePlacement(InStream& stream, int dr, int dc, int step) {
    for (auto [tr, tc] : turtle) {
        int nr = tr + dr;
        int nc = tc + dc;
        if (nr < 0 || nr >= r || nc < 0 || nc >= c) {
            stream.quitf(_wa, "turtle cell leaves map after move %d", step);
        }
        if (board[nr][nc] == '#') {
            stream.quitf(_wa, "turtle cell hits obstacle at (%d, %d) after move %d",
                         nr + 1, nc + 1, step);
        }
    }
}

Claim readClaim(InStream& stream, const char* role) {
    string token = stream.readToken("-1|[URDL]{1,1000000}", format("%s answer", role).c_str());
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %s answer", role);
    }

    if (token == "-1") {
        return {true, -1};
    }

    int dr = 0, dc = 0;
    validatePlacement(stream, dr, dc, 0);

    for (int i = 0; i < (int)token.size(); ++i) {
        if (token[i] == 'U') {
            --dr;
        } else if (token[i] == 'R') {
            ++dc;
        } else if (token[i] == 'D') {
            ++dr;
        } else if (token[i] == 'L') {
            --dc;
        }
        validatePlacement(stream, dr, dc, i + 1);
    }

    if (!reachesHome(dr, dc)) {
        stream.quitf(_wa, "%s path does not place any turtle cell on the home", role);
    }

    return {false, (int)token.size()};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    r = inf.readInt();
    c = inf.readInt();
    board.resize(r);
    for (int i = 0; i < r; ++i) {
        board[i] = inf.readToken(format("[HT#.]{%d}", c).c_str());
        for (int j = 0; j < c; ++j) {
            if (board[i][j] == 'T') {
                turtle.push_back({i, j});
            } else if (board[i][j] == 'H') {
                home = {i, j};
            }
        }
    }

    Claim jury = readClaim(ans, "jury");
    Claim participant = readClaim(ouf, "participant");

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both answers are impossible");
        }
        quitf(_fail, "participant found a valid path of length %d but jury says impossible",
              participant.moves);
    }

    if (participant.impossible) {
        quitf(_wa, "participant says impossible but jury has a path of length %d", jury.moves);
    }
    if (participant.moves < jury.moves) {
        quitf(_fail, "participant found a shorter valid path: participant=%d jury=%d",
              participant.moves, jury.moves);
    }
    if (participant.moves > jury.moves) {
        quitf(_wa, "path is not minimal: participant=%d jury=%d", participant.moves, jury.moves);
    }
    quitf(_ok, "valid minimal path of length %d", participant.moves);
}
