#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int n, m, k;
vector<string> original;

struct Answer {
    int cost;
};

Answer readAnswer(InStream& stream, TResult invalidResult, const char* role) {
    int claimedCost = stream.readInt(0, n * m, format("%s repaint count", role).c_str());
    stream.readEoln();

    vector<string> board(n);
    string rowPattern = "[A-Z]{" + to_string(m) + "," + to_string(m) + "}";
    for (int i = 0; i < n; ++i) {
        board[i] = stream.readToken(rowPattern, format("%s row[%d]", role, i + 1).c_str());
        stream.readEoln();
    }
    stream.readEof();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (board[i][j] != board[i % k][j % k]) {
                stream.quitf(invalidResult,
                             "%s board is not K-periodic at (%d, %d): found %c, expected %c",
                             role,
                             i + 1,
                             j + 1,
                             board[i][j],
                             board[i % k][j % k]);
            }
        }
    }

    int actualCost = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (board[i][j] != original[i][j]) {
                ++actualCost;
            }
        }
    }

    if (claimedCost != actualCost) {
        stream.quitf(invalidResult,
                     "%s repaint count is %d, but supplied board has repaint count %d",
                     role,
                     claimedCost,
                     actualCost);
    }

    return {actualCost};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    k = inf.readInt();
    original.resize(n);
    for (int i = 0; i < n; ++i) {
        original[i] = inf.readToken();
    }

    Answer jury = readAnswer(ans, _fail, "jury");
    Answer participant = readAnswer(ouf, _wa, "participant");

    if (participant.cost > jury.cost) {
        quitf(_wa, "jury has better answer: jury=%d participant=%d", jury.cost, participant.cost);
    }
    if (participant.cost < jury.cost) {
        quitf(_fail, "participant found better answer: jury=%d participant=%d", jury.cost, participant.cost);
    }
    quitf(_ok, "answer=%d", participant.cost);
}
