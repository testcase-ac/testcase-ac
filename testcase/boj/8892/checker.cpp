#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int k;
vector<string> words;

// Reads one answer (a string) from the given stream, validates it against
// the current test case's input words, and returns it.
// If the answer is invalid, quits with _wa for participant stream (ouf)
// or _fail for jury stream (ans).
string readAns(InStream &stream) {
    // Read next token (the palindrome or "0")
    string s = stream.readToken();
    if (s == "0") {
        // Participant or jury says "no palindrome"
        return s;
    }
    // Check it's a palindrome
    string rev = s;
    reverse(rev.begin(), rev.end());
    if (s != rev) {
        stream.quitf(_wa, "string \"%s\" is not a palindrome", s.c_str());
    }
    // Check it can be formed by concatenating two words from the list
    bool found = false;
    for (int i = 0; i < k && !found; i++) {
        int len_i = (int)words[i].size();
        if (len_i >= (int)s.size()) continue;
        // check if s starts with words[i]
        if (s.compare(0, len_i, words[i]) != 0) continue;
        // remainder
        string tail = s.substr(len_i);
        // check if tail equals any word
        for (int j = 0; j < k; j++) {
            if (tail == words[j]) {
                found = true;
                break;
            }
        }
    }
    if (!found) {
        stream.quitf(_wa,
            "string \"%s\" cannot be formed by concatenation of two input words",
            s.c_str());
    }
    return s;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int T = inf.readInt();
    for (int tc = 0; tc < T; tc++) {
        k = inf.readInt();
        words.resize(k);
        for (int i = 0; i < k; i++) {
            words[i] = inf.readToken();
        }
        // Read jury and participant answers for this test case
        string jans = readAns(ans);
        string pans = readAns(ouf);
        // Both say no palindrome
        if (jans == "0" && pans == "0") {
            continue;
        }
        // Jury has palindrome, participant says none
        if (jans != "0" && pans == "0") {
            quitf(_wa, "no palindrome in output, expected \"%s\"", jans.c_str());
        }
        // Jury says none, participant outputs one
        if (jans == "0" && pans != "0") {
            quitf(_wa, "palindrome \"%s\" found but no palindrome exists", pans.c_str());
        }
        // Both provided a palindrome and we already validated each is correct.
        // We accept any correct palindrome, so just continue.
    }
    quitf(_ok, "OK");
    return 0;
}
