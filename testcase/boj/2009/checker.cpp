#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int n;
vector<string> expectedH;
vector<string> expectedR;
vector<string> expectedC;

struct Answer {
    bool possible;
};

Answer readAnswer(InStream& stream) {
    string verdict = stream.readToken("YES|NO", "verdict");

    if (verdict == "NO") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after NO");
        }
        return {false};
    }

    vector<vector<string>> blocks(n, vector<string>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            blocks[i][j] = stream.readToken("[01]{1,100}", format("M[%d][%d]", i + 1, j + 1));
            if ((int)blocks[i][j].size() != n) {
                stream.quitf(_wa,
                             "M[%d][%d] has length %d, expected %d",
                             i + 1, j + 1, (int)blocks[i][j].size(), n);
            }
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after construction");
    }

    vector<string> actualH(n, string(n, '0'));
    vector<string> actualR(n, string(n, '0'));
    vector<string> actualC(n, string(n, '0'));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                if (blocks[i][j][k] == '1') {
                    actualH[j][k] = '1';
                    actualR[i][k] = '1';
                    actualC[i][j] = '1';
                }
            }
        }
    }

    for (int j = 0; j < n; ++j) {
        for (int k = 0; k < n; ++k) {
            if (actualH[j][k] != expectedH[j][k]) {
                stream.quitf(_wa,
                             "H projection differs at row %d column %d: expected %c, found %c",
                             j + 1, k + 1, expectedH[j][k], actualH[j][k]);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < n; ++k) {
            if (actualR[i][k] != expectedR[i][k]) {
                stream.quitf(_wa,
                             "R projection differs at layer %d column %d: expected %c, found %c",
                             i + 1, k + 1, expectedR[i][k], actualR[i][k]);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (actualC[i][j] != expectedC[i][j]) {
                stream.quitf(_wa,
                             "C projection differs at layer %d row %d: expected %c, found %c",
                             i + 1, j + 1, expectedC[i][j], actualC[i][j]);
            }
        }
    }

    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    expectedH.resize(n);
    expectedR.resize(n);
    expectedC.resize(n);

    for (int j = 0; j < n; ++j) {
        expectedH[j] = inf.readToken();
    }
    for (int i = 0; i < n; ++i) {
        expectedR[i] = inf.readToken();
    }
    for (int i = 0; i < n; ++i) {
        expectedC[i] = inf.readToken();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.possible) {
        if (!participant.possible) {
            quitf(_wa, "jury provides a valid construction, but participant answered NO");
        }
        quitf(_ok, "valid construction");
    }

    if (participant.possible) {
        quitf(_fail, "participant provides a valid construction, but jury answered NO");
    }

    quitf(_ok, "both jury and participant answered NO");
}
