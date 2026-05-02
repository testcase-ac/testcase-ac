#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int hexVal(char c) {
    if ('0' <= c && c <= '9') return c - '0';
    return 10 + (c - 'A');
}

// compare two hex strings of same length, lexicographically by value
int cmpHex(const string& a, const string& b) {
    if (a.size() != b.size()) return (int)a.size() < (int)b.size() ? -1 : 1;
    for (int i = 0; i < (int)a.size(); ++i) {
        int va = hexVal(a[i]);
        int vb = hexVal(b[i]);
        if (va < vb) return -1;
        if (va > vb) return 1;
    }
    return 0;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // T is not explicitly bounded in statement, assume up to 100000
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int N = inf.readInt(2, 450, "N");
        inf.readSpace();
        int D = inf.readInt(2, 5, "D"); // overall max D is 5 from test sets
        inf.readEoln();

        // Read S and E as D-digit hex strings
        string S = inf.readToken("[0-9A-F]{1,16}", "S");
        inf.readSpace();
        string E = inf.readToken("[0-9A-F]{1,16}", "E");
        inf.readEoln();

        ensuref((int)S.size() == D, "S must have exactly D=%d digits, got %d", D, (int)S.size());
        ensuref((int)E.size() == D, "E must have exactly D=%d digits, got %d", D, (int)E.size());

        // Check S and E characters are hex digits (already enforced by regex) and S <= E
        int ce = cmpHex(S, E);
        ensuref(ce <= 0, "S must be <= E in numeric value");

        // Read list L of N D-digit hex strings
        vector<string> L(N);
        for (int i = 0; i < N; ++i) {
            if (i > 0) inf.readSpace();
            L[i] = inf.readToken("[0-9A-F]{1,16}", "L_i");
            ensuref((int)L[i].size() == D,
                    "L_%d must have exactly D=%d digits, got %d",
                    i + 1, D, (int)L[i].size());
        }
        inf.readEoln();

        // No further global constraints (like existence of some event) are stated.
        // No need to simulate; probability can be zero per samples.
    }

    inf.readEof();
}
