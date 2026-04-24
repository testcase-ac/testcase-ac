#include "testlib.h"
#include <vector>
#include <string>

using namespace std;

int m, n, curTest;

// Reads a Hamiltonian cycle from 'stream', checks its correctness on the m×n toroidal grid.
// If stream==ouf (participant), errors produce _wa; if stream==ans (jury), errors produce _fail.
void readCycle(InStream &stream) {
    int total = m * n;
    vector< vector<bool> > used(m, vector<bool>(n, false));
    int first_x = -1, first_y = -1;
    int prev_x = -1, prev_y = -1;
    for (int k = 0; k < total; k++) {
        // Each vertex is on its own line, no spaces, format "(i,j)"
        string s = stream.readToken();
        if (s.size() < 5 || s.front() != '(' || s.back() != ')')
            stream.quitf(&stream == &ouf ? _wa : _fail,
                        "test %d: invalid token '%s', expected '(i,j)'", curTest, s.c_str());
        size_t comma = s.find(',');
        if (comma == string::npos)
            stream.quitf(&stream == &ouf ? _wa : _fail,
                        "test %d: invalid token '%s', missing comma", curTest, s.c_str());
        string sx = s.substr(1, comma - 1);
        string sy = s.substr(comma + 1, s.size() - comma - 2);
        for (char c : sx) if (!isdigit(c))
            stream.quitf(&stream == &ouf ? _wa : _fail,
                        "test %d: invalid x-coordinate in '%s'", curTest, s.c_str());
        for (char c : sy) if (!isdigit(c))
            stream.quitf(&stream == &ouf ? _wa : _fail,
                        "test %d: invalid y-coordinate in '%s'", curTest, s.c_str());
        int x = atoi(sx.c_str());
        int y = atoi(sy.c_str());
        if (x < 0 || x >= m || y < 0 || y >= n)
            stream.quitf(&stream == &ouf ? _wa : _fail,
                        "test %d: vertex (%d,%d) out of bounds", curTest, x, y);
        if (used[x][y])
            stream.quitf(&stream == &ouf ? _wa : _fail,
                        "test %d: vertex (%d,%d) is used twice", curTest, x, y);
        used[x][y] = true;
        if (k == 0) {
            first_x = x; first_y = y;
        } else {
            // Check adjacency on toroidal grid
            bool adj = false;
            // same row, columns differ by 1 mod n
            if (x == prev_x) {
                if ((y + 1) % n == prev_y || (prev_y + 1) % n == y)
                    adj = true;
            }
            // same column, rows differ by 1 mod m
            if (y == prev_y) {
                if ((x + 1) % m == prev_x || (prev_x + 1) % m == x)
                    adj = true;
            }
            if (!adj)
                stream.quitf(&stream == &ouf ? _wa : _fail,
                            "test %d: vertices (%d,%d) and (%d,%d) are not adjacent",
                            curTest, prev_x, prev_y, x, y);
        }
        prev_x = x; prev_y = y;
    }
    // check cycle closure between last and first
    {
        bool adj = false;
        if (first_x == prev_x) {
            if ((first_y + 1) % n == prev_y || (prev_y + 1) % n == first_y)
                adj = true;
        }
        if (first_y == prev_y) {
            if ((first_x + 1) % m == prev_x || (prev_x + 1) % m == first_x)
                adj = true;
        }
        if (!adj)
            stream.quitf(&stream == &ouf ? _wa : _fail,
                        "test %d: vertices (%d,%d) and (%d,%d) are not adjacent (cycle not closed)",
                        curTest, prev_x, prev_y, first_x, first_y);
    }
    // check all visited
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (!used[i][j])
                stream.quitf(&stream == &ouf ? _wa : _fail,
                            "test %d: vertex (%d,%d) is not visited", curTest, i, j);
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int T = inf.readInt();
    for (int t = 0; t < T; t++) {
        curTest = t + 1;
        m = inf.readInt();
        n = inf.readInt();
        // read existence flag from jury and participant
        int jflag = ans.readInt();
        int pflag = ouf.readInt();
        if (jflag != -1 && jflag != 1)
            quitf(_fail, "test %d: jury flag is %d, expected -1 or 1", curTest, jflag);
        if (pflag != -1 && pflag != 1)
            quitf(_wa,   "test %d: participant flag is %d, expected -1 or 1", curTest, pflag);
        if (jflag == -1) {
            if (pflag != -1)
                quitf(_wa, "test %d: no solution expected, but participant printed a cycle", curTest);
            // nothing more to check for this test
        } else {
            // solution exists
            if (pflag == -1)
                quitf(_wa, "test %d: solution exists, but participant printed -1", curTest);
            // read & validate jury's cycle first (should not fail)
            readCycle(ans);
            // read & validate participant's cycle
            readCycle(ouf);
        }
    }
    quitf(_ok, "All tests passed");
    return 0;
}
