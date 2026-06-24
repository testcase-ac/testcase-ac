#include "testlib.h"

#include <vector>

using namespace std;

int n;
vector<int> correctAnswer;
vector<bool> guessedCorrect;

struct Answer {
    vector<int> selected;
};

Answer readAnswer(InStream& stream) {
    vector<int> selected(n);
    for (int i = 0; i < n; ++i) {
        selected[i] = stream.readInt(1, 5, format("answer[%d]", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after answer sequence");
    }

    for (int i = 0; i < n; ++i) {
        bool isCorrect = selected[i] == correctAnswer[i];
        if (guessedCorrect[i] && !isCorrect) {
            stream.quitf(_wa,
                         "answer[%d]=%d should match correct answer %d",
                         i + 1,
                         selected[i],
                         correctAnswer[i]);
        }
        if (!guessedCorrect[i] && isCorrect) {
            stream.quitf(_wa,
                         "answer[%d]=%d should not match correct answer",
                         i + 1,
                         selected[i]);
        }
        if (i > 0 && selected[i - 1] == selected[i]) {
            stream.quitf(_wa,
                         "answers at positions %d and %d are both %d",
                         i,
                         i + 1,
                         selected[i]);
        }
    }

    return {selected};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    int m = inf.readInt();

    correctAnswer.resize(n);
    for (int i = 0; i < n; ++i) {
        correctAnswer[i] = inf.readInt();
    }

    guessedCorrect.assign(n, false);
    for (int i = 0; i < m; ++i) {
        int index = inf.readInt();
        guessedCorrect[index - 1] = true;
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    quitf(_ok,
          "valid answer sequence of length %d, jury first answer %d, participant first answer %d",
          n,
          jury.selected[0],
          participant.selected[0]);
}
