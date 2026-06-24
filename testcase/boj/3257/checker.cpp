#include "testlib.h"

#include <string>

using namespace std;

string firstWord;
string secondWord;
string screenWord;

struct Answer {
    string labels;
};

Answer readAnswer(InStream& stream) {
    string labels = stream.readToken("[12]+", "labels");
    stream.readEoln();
    stream.readEof();

    if (labels.size() != screenWord.size()) {
        stream.quitf(_wa,
                     "labels length is %d, expected %d",
                     static_cast<int>(labels.size()),
                     static_cast<int>(screenWord.size()));
    }

    string firstClaim;
    string secondClaim;
    for (int i = 0; i < static_cast<int>(labels.size()); ++i) {
        if (labels[i] == '1') {
            firstClaim.push_back(screenWord[i]);
        } else {
            secondClaim.push_back(screenWord[i]);
        }
    }

    if (firstClaim != firstWord) {
        stream.quitf(_wa, "positions labeled 1 reconstruct '%s' instead of '%s'",
                     firstClaim.c_str(), firstWord.c_str());
    }
    if (secondClaim != secondWord) {
        stream.quitf(_wa, "positions labeled 2 reconstruct '%s' instead of '%s'",
                     secondClaim.c_str(), secondWord.c_str());
    }

    return {labels};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    firstWord = inf.readToken();
    secondWord = inf.readToken();
    screenWord = inf.readToken();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    quitf(_ok, "valid labeling accepted, jury='%s', participant='%s'",
          jury.labels.c_str(), participant.labels.c_str());
}
