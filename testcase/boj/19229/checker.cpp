#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int n;
int l;
int k;
string letters;

struct Answer {
    vector<string> words;
    string objective;
};

Answer readAnswer(InStream& stream) {
    vector<int> remaining(26, 0);
    for (char ch : letters) {
        ++remaining[ch - 'a'];
    }

    vector<string> words(n);
    for (int i = 0; i < n; ++i) {
        words[i] = stream.readWord(format("[a-z]{%d}", l), format("word[%d]", i + 1).c_str());
        for (char ch : words[i]) {
            int idx = ch - 'a';
            --remaining[idx];
            if (remaining[idx] < 0) {
                stream.quitf(_wa, "letter '%c' is used too many times", ch);
            }
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d words", n);
    }

    for (int i = 1; i < n; ++i) {
        if (words[i - 1] > words[i]) {
            stream.quitf(_wa, "words are not sorted at positions %d and %d", i, i + 1);
        }
    }
    for (int i = 0; i < 26; ++i) {
        if (remaining[i] != 0) {
            stream.quitf(_wa, "letter '%c' is used %d fewer times than required", char('a' + i), remaining[i]);
        }
    }

    return {words, words[k - 1]};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    l = inf.readInt();
    k = inf.readInt();
    letters = inf.readWord(format("[a-z]{%d}", n * l), "letters");

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.objective < jury.objective) {
        quitf(_fail,
              "participant has better k-th word: participant=%s jury=%s",
              participant.objective.c_str(),
              jury.objective.c_str());
    }
    if (participant.objective > jury.objective) {
        quitf(_wa,
              "participant has worse k-th word: participant=%s jury=%s",
              participant.objective.c_str(),
              jury.objective.c_str());
    }

    quitf(_ok, "k-th word is %s", participant.objective.c_str());
}
