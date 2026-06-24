#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int n, m;
vector<string> board;

struct Answer {
    bool impossible;
    int row;
    int col;
};

bool isValidCenter(int row, int col) {
    vector<int> scoreCount(11, 0);

    for (int dr = -9; dr <= 9; ++dr) {
        for (int dc = -9; dc <= 9; ++dc) {
            int r = row + dr;
            int c = col + dc;
            if (r < 0 || r >= n || c < 0 || c >= m || board[r][c] != '1') {
                continue;
            }

            int score = 10 - max(abs(dr), abs(dc));
            ++scoreCount[score];
        }
    }

    for (int score = 1; score <= 10; ++score) {
        if (scoreCount[score] != 1) {
            return false;
        }
    }
    return true;
}

Answer readAnswer(InStream& stream) {
    int first = stream.readInt(-1, n - 1, "row or -1");
    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true, -1, -1};
    }

    int col = stream.readInt(0, m - 1, "column");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after center");
    }

    if (!isValidCenter(first, col)) {
        stream.quitf(_wa, "center (%d, %d) does not get each score from 1 to 10 exactly once",
                     first, col);
    }

    return {false, first, col};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    board.resize(n);
    for (int i = 0; i < n; ++i) {
        board[i] = inf.readToken();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both answers report impossible");
        }
        quitf(_fail, "participant found valid center (%d, %d) while jury reports impossible",
              participant.row, participant.col);
    }

    if (participant.impossible) {
        quitf(_wa, "jury has valid center (%d, %d), participant reports impossible",
              jury.row, jury.col);
    }

    quitf(_ok, "valid center (%d, %d)", participant.row, participant.col);
}
