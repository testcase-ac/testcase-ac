#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

set<string> inputWords;

bool isMixedExtension(const string& longerWord, const string& shorterWord) {
    if (longerWord.size() != shorterWord.size() + 1) {
        return false;
    }

    string longer = longerWord;
    string shorter = shorterWord;
    sort(longer.begin(), longer.end());
    sort(shorter.begin(), shorter.end());

    int skipped = 0;
    size_t i = 0;
    size_t j = 0;
    while (i < longer.size() && j < shorter.size()) {
        if (longer[i] == shorter[j]) {
            ++i;
            ++j;
        } else {
            ++skipped;
            ++i;
            if (skipped > 1) {
                return false;
            }
        }
    }
    return true;
}

struct Answer {
    int length;
};

Answer readAnswer(InStream& stream) {
    vector<string> chain;
    set<string> used;

    while (!stream.seekEof()) {
        string word = stream.readToken("[a-z]{1,20}", format("chain[%d]", int(chain.size()) + 1).c_str());
        if (!inputWords.count(word)) {
            stream.quitf(_wa, "chain word %d is not present in the input: %s", int(chain.size()) + 1, word.c_str());
        }
        if (!used.insert(word).second) {
            stream.quitf(_wa, "chain word %d is repeated: %s", int(chain.size()) + 1, word.c_str());
        }
        chain.push_back(word);
    }

    if (chain.empty()) {
        stream.quitf(_wa, "chain is empty");
    }

    for (int i = 1; i < int(chain.size()); ++i) {
        if (!isMixedExtension(chain[i], chain[i - 1])) {
            stream.quitf(_wa,
                         "chain word %d (%s) is not a mixed extension of word %d (%s)",
                         i + 1,
                         chain[i].c_str(),
                         i,
                         chain[i - 1].c_str());
        }
    }

    return {int(chain.size())};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    while (!inf.seekEof()) {
        string word = inf.readToken("[a-z]{1,20}", "input word");
        inputWords.insert(word);
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.length < jury.length) {
        quitf(_wa,
              "participant chain is shorter than jury chain: participant=%d jury=%d",
              participant.length,
              jury.length);
    }
    if (participant.length > jury.length) {
        quitf(_fail,
              "participant found a longer valid chain: participant=%d jury=%d",
              participant.length,
              jury.length);
    }

    quitf(_ok, "valid chain of length %d", participant.length);
}
