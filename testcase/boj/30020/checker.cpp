#include "testlib.h"

#include <string>

using namespace std;

int A, B;

struct Answer {
    bool possible;
};

Answer readAnswer(InStream& stream) {
    string verdict = stream.readToken("[A-Z]+", "verdict");
    if (verdict == "NO") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after NO");
        }
        return {false};
    }
    if (verdict != "YES") {
        stream.quitf(_wa, "verdict must be YES or NO, found '%s'", verdict.c_str());
    }

    int k = stream.readInt(1, A, "K");
    int totalA = 0;
    int totalB = 0;
    for (int i = 0; i < k; ++i) {
        string s = stream.readToken("[ab]+", format("S[%d]", i + 1).c_str());
        int countA = 0;
        int countB = 0;
        for (int j = 0; j < (int)s.size(); ++j) {
            if (s[j] == 'a') {
                ++countA;
            } else {
                ++countB;
            }
            if (j > 0 && s[j] == s[j - 1]) {
                stream.quitf(_wa, "S[%d] is not alternating at positions %d and %d", i + 1, j, j + 1);
            }
        }
        if (countA == 0 || countB == 0) {
            stream.quitf(_wa, "S[%d] must contain at least one patty and one cheese", i + 1);
        }
        if (countA != countB + 1) {
            stream.quitf(_wa,
                         "S[%d] has %d patties and %d cheeses, expected patties = cheeses + 1",
                         i + 1,
                         countA,
                         countB);
        }
        totalA += countA;
        totalB += countB;
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after construction");
    }

    if (totalA != A || totalB != B) {
        stream.quitf(_wa,
                     "used %d patties and %d cheeses, expected %d patties and %d cheeses",
                     totalA,
                     totalB,
                     A,
                     B);
    }
    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    A = inf.readInt();
    B = inf.readInt();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.possible) {
        if (!participant.possible) {
            quitf(_wa, "jury has a construction but participant says NO");
        }
        quitf(_ok, "valid construction");
    }

    if (participant.possible) {
        quitf(_fail, "participant found a valid construction while jury says NO");
    }
    quitf(_ok, "both outputs say NO");
}
