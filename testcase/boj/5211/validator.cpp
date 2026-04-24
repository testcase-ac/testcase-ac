#include "testlib.h"
#include <string>
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the entire music string: only A-G and '|' allowed
    string s = inf.readToken("[A-G\\|]+", "s");
    int n = (int)s.size();

    // Length constraints
    ensuref(n >= 5 && n <= 100, "Length of s must be between 5 and 100, but got %d", n);

    // '|' must not appear at the ends
    ensuref(s.front() != '|', "'|' appears at the beginning");
    ensuref(s.back() != '|', "'|' appears at the end");

    // No consecutive '|' allowed
    for (int i = 1; i < n; i++) {
        ensuref(!(s[i] == '|' && s[i-1] == '|'),
                "Consecutive '|' at positions %d and %d", i-1, i);
    }

    // Split measures by '|'
    vector<string> measures;
    {
        string cur;
        for (char c : s) {
            if (c == '|') {
                // measure separator
                ensuref(!cur.empty(), "Empty measure detected");
                measures.push_back(cur);
                cur.clear();
            } else {
                // must be note A-G (already regex-checked)
                cur.push_back(c);
            }
        }
        // last measure
        ensuref(!cur.empty(), "Empty last measure detected");
        measures.push_back(cur);
    }

    // Center notes sets
    const set<char> minorC = {'A','D','E'};
    const set<char> majorC = {'C','F','G'};

    // Count first-note center occurrences
    int cntMinor = 0, cntMajor = 0;
    for (int i = 0; i < (int)measures.size(); i++) {
        char lead = measures[i][0];
        if (minorC.count(lead)) cntMinor++;
        if (majorC.count(lead)) cntMajor++;
    }

    // If tie, last note must break tie
    if (cntMinor != cntMajor) {
        // OK, determined by counts
    } else {
        // tie-break by the last note of s (ignore pipes)
        char lastNote = 0;
        for (int i = n-1; i >= 0; i--) {
            if (s[i] != '|') {
                lastNote = s[i];
                break;
            }
        }
        // lastNote must be in exactly one of minorC or majorC
        bool isMinorNote = minorC.count(lastNote);
        bool isMajorNote = majorC.count(lastNote);
        ensuref(isMinorNote ^ isMajorNote,
                "Tie in center counts (%d) and last note '%c' does not break tie",
                cntMinor, lastNote);
    }

    inf.readEoln();
    inf.readEof();
    return 0;
}
