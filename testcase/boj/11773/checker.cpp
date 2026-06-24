#include "testlib.h"

#include <set>
#include <sstream>
#include <string>

using namespace std;

int A, B;

struct Essay {
    int words;
    int distinct;
};

Essay readEssay(InStream& stream) {
    string line = stream.readLine();
    stream.readEof();

    if (line.empty()) {
        stream.quitf(_wa, "essay is empty");
    }

    for (int i = 0; i < (int)line.size(); ++i) {
        char c = line[i];
        if (!(c == ' ' || ('a' <= c && c <= 'z'))) {
            stream.quitf(_wa, "invalid character at position %d", i + 1);
        }
    }

    if (line.front() == ' ' || line.back() == ' ') {
        stream.quitf(_wa, "essay has leading or trailing space");
    }
    for (int i = 1; i < (int)line.size(); ++i) {
        if (line[i - 1] == ' ' && line[i] == ' ') {
            stream.quitf(_wa, "essay has consecutive spaces at positions %d and %d", i, i + 1);
        }
    }

    stringstream ss(line);
    string word;
    set<string> vocabulary;
    int words = 0;
    while (ss >> word) {
        ++words;
        if ((int)word.size() > 15) {
            stream.quitf(_wa, "word %d has length %d, maximum is 15", words, (int)word.size());
        }
        vocabulary.insert(word);
    }

    if (words < A || words > B) {
        stream.quitf(_wa, "essay has %d words, expected between %d and %d", words, A, B);
    }

    int requiredDistinct = (B + 1) / 2;
    if ((int)vocabulary.size() < requiredDistinct) {
        stream.quitf(_wa, "essay has %d distinct words, expected at least %d",
                     (int)vocabulary.size(), requiredDistinct);
    }

    return {words, (int)vocabulary.size()};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    A = inf.readInt();
    B = inf.readInt();

    Essay jury = readEssay(ans);
    Essay participant = readEssay(ouf);

    quitf(_ok, "valid essay with %d words and %d distinct words; jury has %d words and %d distinct words",
          participant.words, participant.distinct, jury.words, jury.distinct);
}
