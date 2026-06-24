#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Answer {
    vector<pair<int, int>> ranges;
};

static int n;
static vector<int> initialBoard;

static Answer readAnswer(InStream& stream) {
    Answer answer;

    for (int line = 0; line < 2; ++line) {
        int left = stream.readInt(1, n, format("range[%d].left", line + 1).c_str());
        stream.readSpace();
        int right = stream.readInt(1, n, format("range[%d].right", line + 1).c_str());
        if (left > right) {
            stream.quitf(_wa, "range %d has left endpoint %d greater than right endpoint %d",
                         line + 1, left, right);
        }
        stream.readEoln();
        answer.ranges.push_back({left, right});
    }

    stream.readEof();
    return answer;
}

static bool restoresInitialBoard(const Answer& answer) {
    vector<int> board = initialBoard;
    for (auto [left, right] : answer.ranges) {
        reverse(board.begin() + left - 1, board.begin() + right);
    }

    for (int i = 0; i < n; ++i) {
        if (board[i] != i + 1) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    initialBoard.resize(n);
    for (int i = 0; i < n; ++i) {
        initialBoard[i] = inf.readInt();
    }

    Answer jury = readAnswer(ans);
    if (!restoresInitialBoard(jury)) {
        quitf(_fail, "jury answer does not restore the board");
    }

    Answer participant = readAnswer(ouf);
    if (!restoresInitialBoard(participant)) {
        quitf(_wa, "participant answer does not restore the board");
    }

    quitf(_ok, "participant answer restores the board");
}
