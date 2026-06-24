#include "testlib.h"

#include <array>
#include <string>

using namespace std;

int n;
array<bool, 26> allowed;
int alphabetSize;

struct Answer {
    int length;
};

Answer readAnswer(InStream& stream) {
    string output = stream.readToken("[a-z]+", "answer");
    stream.readEoln();
    stream.readEof();

    int seenCount = 0;
    int completedBlocks = 0;
    array<bool, 26> seen{};

    for (int i = 0; i < (int)output.size(); ++i) {
        int c = output[i] - 'a';
        if (!allowed[c]) {
            stream.quitf(_wa, "answer[%d] uses character '%c' outside the input alphabet", i + 1, output[i]);
        }

        if (!seen[c]) {
            seen[c] = true;
            ++seenCount;
            if (seenCount == alphabetSize) {
                ++completedBlocks;
                seen.fill(false);
                seenCount = 0;
            }
        }
    }

    if (completedBlocks < n) {
        stream.quitf(_wa,
                     "answer covers only %d complete alphabet blocks, but %d are required",
                     completedBlocks,
                     n);
    }

    return {(int)output.size()};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    string alphabet = inf.readToken();

    allowed.fill(false);
    alphabetSize = (int)alphabet.size();
    for (char ch : alphabet) {
        allowed[ch - 'a'] = true;
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.length > jury.length) {
        quitf(_wa,
              "participant answer is longer than jury answer: participant=%d jury=%d",
              participant.length,
              jury.length);
    }
    if (participant.length < jury.length) {
        quitf(_fail,
              "participant found a shorter valid answer: participant=%d jury=%d",
              participant.length,
              jury.length);
    }

    quitf(_ok, "valid shortest answer with length %d", participant.length);
}
