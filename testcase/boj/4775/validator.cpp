#include "testlib.h"
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dictionary size
    int n = inf.readInt(0, 100000, "n");
    inf.readEoln();

    // Read dictionary words, ensure lowercase letters, apostrophes or hyphens, no duplicates
    set<string> dict;
    for (int i = 0; i < n; i++) {
        // readToken ensures no spaces, then we enforce pattern
        string w = inf.readToken("[a-z'-]+", "dict_word");
        inf.readEoln();
        // check duplicates
        ensuref(!dict.count(w),
                "Duplicate word in dictionary at line %d: '%s'", i+2, w.c_str());
        dict.insert(w);
    }

    // Read number of emails
    int m = inf.readInt(0, 100000, "m");
    inf.readEoln();

    // For each email, read words until "-1"
    for (int e = 1; e <= m; e++) {
        int cnt = 0;
        while (true) {
            // read entire line (one token per line in email)
            string s = inf.readLine("[^]+", "email_line");
            // check for terminator
            if (s == "-1") {
                break;
            }
            // must have at least one word before terminator
            cnt++;
            // each character must be a-z or apostrophe or hyphen
            for (int i = 0; i < (int)s.size(); i++) {
                char c = s[i];
                ensuref((c >= 'a' && c <= 'z') || c == '\'' || c == '-',
                        "Invalid character in email %d, word %d: '%c'", e, cnt, c);
            }
        }
        // ensure email had at least one word
        ensuref(cnt > 0, "Email %d has no words before -1", e);
    }

    // No extra content
    inf.readEof();
    return 0;
}
