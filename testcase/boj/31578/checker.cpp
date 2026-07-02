#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int n, k;
vector<string> words;

struct Answer {
    bool possible;
    vector<int> group;
};

bool sharesSubstring(const string& a, const string& b) {
    if ((int)a.size() < k || (int)b.size() < k) {
        return false;
    }
    for (int i = 0; i + k <= (int)a.size(); ++i) {
        for (int j = 0; j + k <= (int)b.size(); ++j) {
            bool same = true;
            for (int offset = 0; offset < k; ++offset) {
                if (a[i + offset] != b[j + offset]) {
                    same = false;
                    break;
                }
            }
            if (same) {
                return true;
            }
        }
    }
    return false;
}

Answer readAnswer(InStream& stream) {
    string verdict = stream.readWord();
    if (verdict == "No") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after No");
        }
        return {false, {}};
    }
    if (verdict != "Yes") {
        stream.quitf(_wa, "verdict must be Yes or No, found '%s'", verdict.c_str());
    }

    vector<int> group(n);
    vector<int> count(3, 0);
    for (int i = 0; i < n; ++i) {
        group[i] = stream.readInt(1, 2, format("wordbook[%d]", i + 1).c_str());
        ++count[group[i]];
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after Yes assignment");
    }
    if (count[1] == 0 || count[2] == 0) {
        stream.quitf(_wa, "both wordbooks must contain at least one word");
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (group[i] == group[j] && sharesSubstring(words[i], words[j])) {
                stream.quitf(_wa,
                             "words %d and %d are in wordbook %d and share a substring of length %d",
                             i + 1,
                             j + 1,
                             group[i],
                             k);
            }
        }
    }

    return {true, group};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    k = inf.readInt();
    words.resize(n);
    for (int i = 0; i < n; ++i) {
        words[i] = inf.readWord();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.possible) {
        if (!participant.possible) {
            quitf(_wa, "jury has a valid Yes assignment, participant answered No");
        }
        quitf(_ok, "valid Yes assignment");
    }

    if (participant.possible) {
        quitf(_fail, "participant found a valid Yes assignment while jury answered No");
    }

    quitf(_ok, "both answered No");
}
