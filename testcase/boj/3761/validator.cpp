#include "testlib.h"
#include <string>
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int t = inf.readInt(1, 100000, "t");
    inf.readEoln();

    for (int tc = 1; tc <= t; tc++) {
        setTestCase(tc);

        // Read n
        int n = inf.readInt(1, 26, "n");
        inf.readEoln();

        // Read 2n names: first n males (lowercase), then n females (uppercase)
        vector<char> maleNames, femaleNames;
        maleNames.reserve(n);
        femaleNames.reserve(n);
        vector<bool> maleUsed(26, false), femaleUsed(26, false);
        for (int i = 0; i < 2 * n; i++) {
            if (i > 0) inf.readSpace();
            string s = inf.readToken("[a-zA-Z]", "name");
            ensuref(s.size() == 1,
                    "Name token must be a single letter, got '%s'", s.c_str());
            char c = s[0];
            if (i < n) {
                // Male names: lowercase
                ensuref(c >= 'a' && c <= 'z',
                        "Name %d must be lowercase for a male, got '%c'", i+1, c);
                int idx = c - 'a';
                ensuref(!maleUsed[idx],
                        "Duplicate male name '%c'", c);
                maleUsed[idx] = true;
                maleNames.push_back(c);
            } else {
                // Female names: uppercase
                ensuref(c >= 'A' && c <= 'Z',
                        "Name %d must be uppercase for a female, got '%c'", i+1, c);
                int idx = c - 'A';
                ensuref(!femaleUsed[idx],
                        "Duplicate female name '%c'", c);
                femaleUsed[idx] = true;
                femaleNames.push_back(c);
            }
        }
        inf.readEoln();

        // Build existence maps for quick lookup
        vector<bool> maleExists(26, false), femaleExists(26, false);
        for (char c : maleNames)   maleExists[c - 'a'] = true;
        for (char c : femaleNames) femaleExists[c - 'A'] = true;

        // Read male preference lists
        vector<bool> maleListSeen(26, false);
        for (int i = 0; i < n; i++) {
            string line = inf.readLine("[^]+", "male_pref");
            // Format must be: x:YYYY... (length = 2 + n)
            ensuref((int)line.size() == 2 + n,
                    "Male preference line %d length is %d, expected %d",
                    i+1, (int)line.size(), 2 + n);
            char m = line[0];
            ensuref(m >= 'a' && m <= 'z',
                    "Line %d: first char '%c' not a lowercase male", i+1, m);
            int mi = m - 'a';
            ensuref(maleExists[mi],
                    "Line %d: unknown male name '%c'", i+1, m);
            ensuref(!maleListSeen[mi],
                    "Line %d: duplicate preference list for male '%c'", i+1, m);
            maleListSeen[mi] = true;
            ensuref(line[1] == ':',
                    "Line %d: missing ':' after male name", i+1);

            vector<bool> seenF(26, false);
            for (int j = 0; j < n; j++) {
                char f = line[2 + j];
                ensuref(f >= 'A' && f <= 'Z',
                        "Line %d: char at pos %d '%c' not an uppercase female",
                        i+1, 2+j, f);
                int fi = f - 'A';
                ensuref(femaleExists[fi],
                        "Line %d: unknown female '%c'", i+1, f);
                ensuref(!seenF[fi],
                        "Line %d: duplicate female '%c' in preference", i+1, f);
                seenF[fi] = true;
            }
        }
        // Ensure every male has a preference list
        for (char m : maleNames) {
            ensuref(maleListSeen[m - 'a'],
                    "No preference list provided for male '%c'", m);
        }

        // Read female preference lists
        vector<bool> femaleListSeen(26, false);
        for (int i = 0; i < n; i++) {
            string line = inf.readLine("[^]+", "female_pref");
            ensuref((int)line.size() == 2 + n,
                    "Female preference line %d length is %d, expected %d",
                    i+1, (int)line.size(), 2 + n);
            char F = line[0];
            ensuref(F >= 'A' && F <= 'Z',
                    "Line %d: first char '%c' not an uppercase female", i+1, F);
            int fi = F - 'A';
            ensuref(femaleExists[fi],
                    "Line %d: unknown female name '%c'", i+1, F);
            ensuref(!femaleListSeen[fi],
                    "Line %d: duplicate preference list for female '%c'", i+1, F);
            femaleListSeen[fi] = true;
            ensuref(line[1] == ':',
                    "Line %d: missing ':' after female name", i+1);

            vector<bool> seenM(26, false);
            for (int j = 0; j < n; j++) {
                char m = line[2 + j];
                ensuref(m >= 'a' && m <= 'z',
                        "Line %d: char at pos %d '%c' not a lowercase male",
                        i+1, 2+j, m);
                int mi = m - 'a';
                ensuref(maleExists[mi],
                        "Line %d: unknown male '%c'", i+1, m);
                ensuref(!seenM[mi],
                        "Line %d: duplicate male '%c' in preference", i+1, m);
                seenM[mi] = true;
            }
        }
        // Ensure every female has a preference list
        for (char F : femaleNames) {
            ensuref(femaleListSeen[F - 'A'],
                    "No preference list provided for female '%c'", F);
        }
    }

    inf.readEof();
    return 0;
}
