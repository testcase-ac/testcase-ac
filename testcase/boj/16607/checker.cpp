#include "testlib.h"
#include <vector>
#include <set>
#include <string>
#include <cstdint>
using namespace std;

const int64_t COORD_LIMIT = 1000000000LL;
const int64_t BORDER = COORD_LIMIT + 1;

string s; // sequence of moves

// Read and validate one answer (jury or participant).
// Returns true if the answer is "impossible", false if it's a valid board.
// On invalid output, quits with _wa if stream == ouf, or _fail if stream == ans.
bool readAns(InStream &stream) {
    stream.skipBlanks();
    if (stream.eof()) {
        stream.quitf(_wa, "unexpected end of output");
    }
    string tok = stream.readToken();
    if (tok == "impossible") {
        // No more tokens expected
        stream.skipBlanks();
        if (!stream.eof()) {
            stream.quitf(_wa, "extra tokens after 'impossible'");
        }
        return true;
    }
    // Otherwise, tok should be starting x coordinate
    int64_t x, y;
    try {
        x = stoll(tok);
    } catch (...) {
        stream.quitf(_wa, "expected integer x or 'impossible', found '%s'", tok.c_str());
    }
    if (x < -COORD_LIMIT || x > COORD_LIMIT) {
        stream.quitf(_wa, "x = %lld is out of bounds", x);
    }
    y = stream.readInt(-COORD_LIMIT, COORD_LIMIT, "y");
    // Number of blocks
    int n = stream.readInt(0, 10000, "n");
    vector<pair<int64_t,int64_t>> blocks;
    blocks.reserve(n);
    set<pair<int64_t,int64_t>> blockSet;
    for (int i = 0; i < n; i++) {
        int64_t bx = stream.readInt(-COORD_LIMIT, COORD_LIMIT, "block.x");
        int64_t by = stream.readInt(-COORD_LIMIT, COORD_LIMIT, "block.y");
        if (bx == 0 && by == 0) {
            stream.quitf(_wa, "block at the hole (0,0) is not allowed");
        }
        pair<int64_t,int64_t> p = make_pair(bx, by);
        if (blockSet.count(p)) {
            stream.quitf(_wa, "duplicate block at (%lld,%lld)", bx, by);
        }
        blockSet.insert(p);
        blocks.push_back(p);
    }
    // Now simulate the ball
    int64_t cx = x, cy = y;
    auto is_blocked = [&](int64_t ux, int64_t uy)->bool {
        // border rows/columns at +-BORDER
        if (ux == BORDER || ux == -BORDER) return true;
        if (uy == BORDER || uy == -BORDER) return true;
        return blockSet.count(make_pair(ux, uy)) > 0;
    };
    for (size_t i = 0; i < s.size(); i++) {
        char c = s[i];
        if (cx == 0 && cy == 0) {
            stream.quitf(_wa, "ball is already in hole before move %d", int(i+1));
        }
        int dx = 0, dy = 0;
        if (c == 'L') dx = -1;
        else if (c == 'R') dx = +1;
        else if (c == 'U') dy = +1;
        else if (c == 'D') dy = -1;
        // Check immediate next cell
        int64_t nx = cx + dx, ny = cy + dy;
        if (is_blocked(nx, ny)) {
            stream.quitf(_wa, "zero movement on move %d at position (%lld,%lld)", int(i+1), cx, cy);
        }
        // Move until blocked or hole
        while (true) {
            cx = nx; cy = ny;
            if (cx == 0 && cy == 0) {
                // fell into hole
                break;
            }
            nx = cx + dx; ny = cy + dy;
            if (is_blocked(nx, ny)) {
                // stop before block
                break;
            }
        }
        if (cx == 0 && cy == 0) {
            // fell into hole on this move
            if (i + 1 < s.size()) {
                stream.quitf(_wa, "ball falls into hole on move %d but %d moves remain", int(i+1), int(s.size() - (i+1)));
            }
            // otherwise OK, this was final move
        }
        // else ball stopped at (cx,cy), continue
    }
    // after all moves, ball must be in hole
    if (!(cx == 0 && cy == 0)) {
        stream.quitf(_wa, "ball did not fall into hole, ended at (%lld,%lld)", cx, cy);
    }
    return false;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    // read input
    s = inf.readToken();
    // read jury and participant answers
    bool jans = readAns(ans);
    bool pans = readAns(ouf);
    if (jans != pans) {
        if (jans) {
            // jury says impossible, participant found a solution
            quitf(_wa, "participant found a solution but jury says impossible");
        } else {
            // jury found a solution, participant says impossible
            quitf(_wa, "participant says impossible but jury has a solution");
        }
    }
    // both agree
    if (jans) {
        quitf(_ok, "correctly reports impossible");
    } else {
        quitf(_ok, "valid maze");
    }
    return 0;
}
