#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int n, m;
vector<int> initial_ori;          // 0 -> front, 1 -> back
vector< vector<int> > sw;        // sw[i][j] = 0/1

struct Answer {
    bool reachable;
    vector<int> sel;
};

// Read one answer (one line) for desired shift 'shiftY'.
// 'lineNo' is for error messages (1-based among output lines).
Answer readAns(InStream& stream, int shiftY, int lineNo) {
    Answer A;
    // k can be -1 or from 0 to m
    int k = stream.readInt(-1, m, format("k on line %d", lineNo).c_str());
    if (k == -1) {
        // no solution
        A.reachable = false;
        A.sel.clear();
        // consume end of line
        stream.readEoln();
        return A;
    }
    A.reachable = true;
    A.sel.resize(k);
    vector<bool> used(m+1, false);
    for (int i = 0; i < k; i++) {
        int x = stream.readInt(1, m,
                   format("switch index %d on line %d", i+1, lineNo).c_str());
        if (used[x]) {
            stream.quitf(_wa, "duplicate switch %d on line %d", x, lineNo);
        }
        used[x] = true;
        A.sel[i] = x;
    }
    // no extra tokens on this line
    stream.readEoln();
    // Validate the chosen switches actually yield shiftY
    vector<int> cur = initial_ori;
    for (int idx : A.sel) {
        int si = idx - 1;
        for (int j = 0; j < n; j++) {
            if (sw[si][j]) {
                cur[j] ^= 1;
            }
        }
    }
    int sumShift = 0;
    for (int j = 0; j < n; j++) {
        // front(0)-> entering front-to-back => -1, back(1)-> +1
        sumShift += (cur[j] == 0 ? -1 : +1);
    }
    if (sumShift != shiftY) {
        stream.quitf(_wa, "line %d: sum of shifts = %d, expected %d",
                     lineNo, sumShift, shiftY);
    }
    return A;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    // Read input
    n = inf.readInt();
    m = inf.readInt();
    string s;
    inf.readEoln();
    initial_ori.resize(n);
    s = inf.readToken();
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') initial_ori[i] = 0;
        else initial_ori[i] = 1;
    }
    sw.assign(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        string t = inf.readToken();
        for (int j = 0; j < n; j++) {
            sw[i][j] = (t[j] == '1' ? 1 : 0);
        }
    }

    // There should be 2n+1 lines: for shifts -n .. n
    for (int d = -n, lineNo = 1; d <= n; d++, lineNo++) {
        Answer ja = readAns(ans, d, lineNo);
        Answer pa = readAns(ouf, d, lineNo);
        if (!ja.reachable && !pa.reachable) {
            // both say impossible: OK for this line
            continue;
        }
        if (ja.reachable && !pa.reachable) {
            quitf(_wa, "line %d: no solution, expected %d switches",
                  lineNo, (int)ja.sel.size());
        }
        if (!ja.reachable && pa.reachable) {
            quitf(_wa, "line %d: found solution for year %d but none exists",
                  lineNo, d);
        }
        // both reachable and pa validated => OK
    }
    // No extra tokens in participant output
    ouf.skipBlanks();
    if (!ouf.eof()) {
        quitf(_wa, "extra tokens at the end of output");
    }
    quitf(_ok, "correct");
    return 0;
}
