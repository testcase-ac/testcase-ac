#include "testlib.h"
#include <string>
#include <vector>
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: two distinct player names, lowercase a-z, length 1 to 20, separated by one space.
    string p1 = inf.readToken("[a-z]{1,20}", "player1");
    inf.readSpace();
    string p2 = inf.readToken("[a-z]{1,20}", "player2");
    ensuref(p1 != p2, "Player names must be distinct, both are \"%s\"", p1.c_str());
    inf.readEoln();

    // Second line: N, number of past matches: 1 <= N <= 50
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    // Next N lines: each line has 1 to 5 set scores, format A:B where 0 <= A,B <= 99
    for (int i = 1; i <= N; i++) {
        // Read entire line (must be non-empty)
        string line = inf.readLine("[^]+", "score_line");
        int L = (int)line.size();
        // No leading or trailing spaces
        ensuref(L > 0, "Line %d is empty", i);
        ensuref(line[0] != ' ', "Line %d has leading space", i);
        ensuref(line[L-1] != ' ', "Line %d has trailing space", i);
        // Split by single space
        vector<string> tokens;
        int start = 0;
        for (int pos = 0; pos <= L; pos++) {
            if (pos == L || line[pos] == ' ') {
                tokens.push_back(line.substr(start, pos - start));
                start = pos + 1;
            }
        }
        int cnt = (int)tokens.size();
        ensuref(cnt >= 1 && cnt <= 5,
                "Line %d: number of sets %d is out of allowed range [1,5]", i, cnt);
        // Validate each token
        for (int j = 0; j < cnt; j++) {
            const string &tok = tokens[j];
            int m = (int)tok.size();
            // Must contain exactly one colon
            int colon = -1;
            for (int k = 0; k < m; k++) {
                if (tok[k] == ':') {
                    if (colon != -1) colon = -2;
                    else colon = k;
                }
            }
            ensuref(colon >= 1 && colon + 1 < m,
                    "Line %d, set %d: invalid format \"%s\", should be A:B", i, j+1, tok.c_str());
            // Split A and B
            string sa = tok.substr(0, colon);
            string sb = tok.substr(colon+1);
            // Each part length 1 or 2, all digits
            ensuref((int)sa.size() >= 1 && (int)sa.size() <= 2,
                    "Line %d, set %d: games of first player \"%s\" has invalid length", i, j+1, sa.c_str());
            ensuref((int)sb.size() >= 1 && (int)sb.size() <= 2,
                    "Line %d, set %d: games of second player \"%s\" has invalid length", i, j+1, sb.c_str());
            for (char c : sa) {
                ensuref(isdigit(c), "Line %d, set %d: non-digit '%c' in \"%s\"", i, j+1, c, sa.c_str());
            }
            for (char c : sb) {
                ensuref(isdigit(c), "Line %d, set %d: non-digit '%c' in \"%s\"", i, j+1, c, sb.c_str());
            }
            // Convert to integer (0 to 99)
            int a = sa.size() == 2 ? (sa[0]-'0')*10 + (sa[1]-'0') : (sa[0]-'0');
            int b = sb.size() == 2 ? (sb[0]-'0')*10 + (sb[1]-'0') : (sb[0]-'0');
            ensuref(0 <= a && a <= 99,
                    "Line %d, set %d: games of first player %d out of range [0,99]", i, j+1, a);
            ensuref(0 <= b && b <= 99,
                    "Line %d, set %d: games of second player %d out of range [0,99]", i, j+1, b);
        }
    }

    inf.readEof();
    return 0;
}
