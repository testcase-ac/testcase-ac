#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int N;
char pieceType;
// initial excavator positions
vector<vector<bool>> initC;

// A move: from (x,y) to (w,z)
struct Move {
    int x, y, w, z;
};

// Read and validate a solution (from jury or participant).
// Returns true if solution says YES and is valid, false if says NO.
// On any invalid formatting or illegal move, quits with _wa (for ouf) or _fail (for ans).
bool readSol(InStream &stream) {
    // Read YES or NO
    string verdict = stream.readToken();
    if (verdict != "YES" && verdict != "NO") {
        stream.quitf(_fail, "expected YES or NO, found '%s'", verdict.c_str());
    }
    if (verdict == "NO") {
        // No moves should follow
        if (!stream.seekEof()) {
            stream.quitf(_fail, "extra tokens after NO");
        }
        return false;
    }
    // verdict == "YES"
    // Copy initial configuration
    vector<vector<bool>> C = initC;
    int cnt = 0;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            if (C[i][j]) cnt++;
    // Read moves until EOF
    while (!stream.seekEof()) {
        int x = stream.readInt(1, N, "X");
        int y = stream.readInt(1, N, "Y");
        int w = stream.readInt(1, N, "W");
        int z = stream.readInt(1, N, "Z");
        // Check source and target have excavators
        if (!C[x][y])
            stream.quitf(_fail, "no excavator at source (%d,%d)", x, y);
        if (!C[w][z])
            stream.quitf(_fail, "no excavator at target (%d,%d)", w, z);
        // Check movement law
        int dx = abs(x - w), dy = abs(y - z);
        bool ok = false;
        switch (pieceType) {
            case 'R':
                ok = ((dx == 0) ^ (dy == 0)) && (dx + dy >= 1);
                break;
            case 'B':
                ok = (dx == dy) && (dx >= 1);
                break;
            case 'Q':
                ok = ( ((dx == 0) ^ (dy == 0)) || (dx == dy) ) && (dx + dy >= 1);
                break;
            case 'N':
                ok = (dx == 1 && dy == 2) || (dx == 2 && dy == 1);
                break;
            case 'K':
                ok = max(dx, dy) == 1 && (dx + dy >= 1);
                break;
            default:
                stream.quitf(_fail, "unknown piece type '%c'", pieceType);
        }
        if (!ok) {
            stream.quitf(_fail, "illegal move from (%d,%d) to (%d,%d) for piece %c",
                        x, y, w, z, pieceType);
        }
        // Perform move: source removed, target remains
        C[x][y] = false;
        cnt--;
    }
    // After all moves, exactly one excavator must remain
    if (cnt != 1) {
        stream.quitf(_fail, "after moves remaining excavators = %d, expected 1", cnt);
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    // Read input
    N = inf.readInt();
    pieceType = inf.readChar();
    initC.assign(N+1, vector<bool>(N+1, false));
    for (int i = 1; i <= N; i++) {
        string row = inf.readToken();
        if ((int)row.size() != N)
            inf.quitf(_fail, "bad input row length");
        for (int j = 1; j <= N; j++) {
            if (row[j-1] == pieceType) {
                initC[i][j] = true;
            } else if (row[j-1] == '.') {
                // empty
            } else {
                inf.quitf(_fail, "unexpected character '%c' in input", row[j-1]);
            }
        }
    }
    // Read jury and participant solutions
    bool juryYes = readSol(ans);
    bool partYes = readSol(ouf);
    // Compare
    if (!juryYes && !partYes) {
        quitf(_ok, "both say NO");
    }
    if (!juryYes && partYes) {
        quitf(_wa, "participant says YES but no solution exists");
    }
    if (juryYes && !partYes) {
        quitf(_wa, "participant says NO but solution exists");
    }
    // both say YES and validated
    quitf(_ok, "valid solution");
    return 0;
}
