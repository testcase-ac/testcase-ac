#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int R, C;
vector< vector<int> > joy;

// Reads an answer from the given stream, checks validity of the path,
// computes and returns the total joy. On invalid path, quits with WA
// if stream == ouf or FAIL if stream == ans.
long long readAns(InStream &stream) {
    // Read the path as a line
    string s = stream.readLine();
    for(int i = 0; i < (int)s.size(); i++) {
        if(s[i] != 'U' && s[i] != 'D' && s[i] != 'L' && s[i] != 'R') {
            stream.quitf(_wa, "invalid direction '%c' at position %d", s[i], i+1);
        }
    }
    stream.readEof();

    // Prepare visited array
    vector< vector<char> > used(R, vector<char>(C, 0));
    int x = 0, y = 0;
    used[x][y] = 1;
    long long total = joy[x][y];

    // Process moves
    for (int i = 0; i < (int)s.size(); i++) {
        char c = s[i];
        if (c == 'U') {
            x--;
        } else if (c == 'D') {
            x++;
        } else if (c == 'L') {
            y--;
        } else if (c == 'R') {
            y++;
        } else {
            stream.quitf(_wa, "invalid direction '%c' at position %d", c, i+1);
        }
        // Check bounds
        if (x < 0 || x >= R || y < 0 || y >= C) {
            stream.quitf(_wa, "move %d leads out of bounds to (%d,%d)", i+1, x+1, y+1);
        }
        // Check revisit
        if (used[x][y]) {
            stream.quitf(_wa, "cell (%d,%d) visited twice at move %d", x+1, y+1, i+1);
        }
        used[x][y] = 1;
        total += joy[x][y];
    }
    // Check end position
    if (x != R-1 || y != C-1) {
        stream.quitf(_wa, "path does not end at bottom-right, ends at (%d,%d)", x+1, y+1);
    }
    
    // Ensure no extra non-whitespace output
    stream.readEof();
    
    return total;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // Read input
    R = inf.readInt();
    C = inf.readInt();
    joy.assign(R, vector<int>(C));
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            joy[i][j] = inf.readInt();
        }
    }

    // Read jury and participant answers
    long long juryScore = readAns(ans);
    long long partScore = readAns(ouf);

    if (partScore < juryScore) {
        quitf(_wa, "jury's answer is better: %lld vs %lld", juryScore, partScore);
    } else if (partScore == juryScore) {
        quitf(_ok, "optimal joy = %lld", partScore);
    } else {
        quitf(_fail, "participant found a better joy (%lld) than jury (%lld)", partScore, juryScore);
    }
}
