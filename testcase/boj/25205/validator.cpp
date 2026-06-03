#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

namespace {

bool contains(const string& chars, char c) {
    return chars.find(c) != string::npos;
}

bool isInitial(char c) {
    return contains("rsefaqtdwczxvg", c);
}

bool isMedial(char c) {
    return contains("koijpuhynbml", c);
}

bool isFinal(char c) {
    return contains("rsefaqtdwczxvg", c);
}

bool canSplitIntoRestrictedSyllables(const string& s) {
    vector<bool> reachable(s.size() + 1);
    reachable[0] = true;

    for (int i = 0; i < int(s.size()); ++i) {
        if (!reachable[i]) {
            continue;
        }

        if (i + 2 <= int(s.size()) && isInitial(s[i]) && isMedial(s[i + 1])) {
            reachable[i + 2] = true;
        }

        if (i + 3 <= int(s.size()) && isInitial(s[i]) && isMedial(s[i + 1]) &&
            isFinal(s[i + 2])) {
            reachable[i + 3] = true;
        }
    }

    return reachable[s.size()];
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 30, "N");
    inf.readEoln();

    string s = inf.readToken("[a-z]{2,30}", "s");
    inf.readEoln();

    ensuref(int(s.size()) == n, "N is %d, but |s| is %d", n, int(s.size()));
    // CHECK: The statement dump omits the table image. The examples and exclusions
    // imply simple lowercase two-beolsik jamo only: C V with optional final C.
    ensuref(canSplitIntoRestrictedSyllables(s),
            "s cannot be split into restricted Hangul syllable keystrokes");

    inf.readEof();
}
