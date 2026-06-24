#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int n, upperCount, lowerCount;
vector<int> hangerType;

struct Answer {
    bool possible;
    string assignment;
};

Answer readAnswer(InStream& stream) {
    string verdict = stream.readToken("[A-Z]+", "verdict");

    if (verdict == "NO") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after NO");
        }
        return {false, ""};
    }

    if (verdict != "YES") {
        stream.quitf(_wa, "verdict must be YES or NO, found '%s'", verdict.c_str());
    }

    string assignment = stream.readToken("[UD]+", "assignment");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after assignment");
    }

    if ((int)assignment.size() != n) {
        stream.quitf(_wa, "assignment length must be %d, found %d", n, (int)assignment.size());
    }

    int usedUpper = 0;
    int usedLower = 0;
    for (int i = 0; i < n; ++i) {
        char item = assignment[i];
        int type = hangerType[i];

        if (item == 'U') {
            ++usedUpper;
            if (type == 2) {
                stream.quitf(_wa, "hanger %d only accepts D, found U", i + 1);
            }
        } else if (item == 'D') {
            ++usedLower;
            if (type == 1) {
                stream.quitf(_wa, "hanger %d only accepts U, found D", i + 1);
            }
        }
    }

    if (usedUpper != upperCount) {
        stream.quitf(_wa, "assignment uses %d U items, expected %d", usedUpper, upperCount);
    }
    if (usedLower != lowerCount) {
        stream.quitf(_wa, "assignment uses %d D items, expected %d", usedLower, lowerCount);
    }

    return {true, assignment};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    hangerType.resize(n);
    for (int i = 0; i < n; ++i) {
        hangerType[i] = inf.readInt();
    }
    upperCount = inf.readInt();
    lowerCount = inf.readInt();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.possible) {
        if (!participant.possible) {
            quitf(_wa, "jury has a valid assignment, participant answered NO");
        }
        quitf(_ok, "valid assignment");
    }

    if (participant.possible) {
        quitf(_fail, "participant found a valid assignment while jury answered NO");
    }

    quitf(_ok, "both answers are NO");
}
