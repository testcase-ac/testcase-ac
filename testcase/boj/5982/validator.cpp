#include "testlib.h"

#include <set>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int l = inf.readInt(1, 1000, "L");
    inf.readSpace();
    int nw = inf.readInt(1, 1000, "NW");
    inf.readEoln();

    string pattern = inf.readToken("[a-z?]{1,1000}", "P");
    ensuref((int)pattern.size() == l, "P length is %d, expected %d",
            (int)pattern.size(), l);
    inf.readEoln();

    set<string> seen;
    vector<string> words(nw);
    for (int i = 0; i < nw; ++i) {
        words[i] = inf.readToken("[a-z]{1,20}", "W_i");
        ensuref(seen.insert(words[i]).second, "duplicate dictionary word: %s",
                words[i].c_str());
        inf.readEoln();
    }

    vector<bool> reachable(l + 1, false);
    reachable[0] = true;
    for (int pos = 0; pos < l; ++pos) {
        if (!reachable[pos]) {
            continue;
        }
        for (const string& word : words) {
            int len = (int)word.size();
            if (pos + len > l) {
                continue;
            }

            bool matches = true;
            for (int j = 0; j < len; ++j) {
                char c = pattern[pos + j];
                if (c != '?' && c != word[j]) {
                    matches = false;
                    break;
                }
            }
            if (matches) {
                reachable[pos + len] = true;
            }
        }
    }
    // CHECK: The statement asks for a password and gives no impossible-case output.
    ensuref(reachable[l], "password cannot be split into matching dictionary words");

    inf.readEof();
}
