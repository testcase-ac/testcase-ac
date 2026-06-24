#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int n, m, targetLen;
vector<string> board;
string target;

struct Claim {
    int claimedCount;
    int achievedCount;
    int length;
};

Claim readAnswer(InStream& stream) {
    int claimedCount = stream.readInt(0, n * m, "C");
    stream.readSpace();
    int length = stream.readInt(1, 1000000, "L");
    stream.readEoln();

    string actions = stream.readToken("[UDLRP]+", "actions");
    if ((int)actions.size() != length) {
        stream.quitf(_wa, "L is %d but action string length is %d",
                     length, (int)actions.size());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after action string");
    }

    vector<vector<bool>> picked(n, vector<bool>(m, false));
    int r = 0;
    int c = 0;
    int achievedCount = 0;
    string inventory;

    for (int i = 0; i < length; ++i) {
        char action = actions[i];
        if (action == 'U') {
            --r;
        } else if (action == 'D') {
            ++r;
        } else if (action == 'L') {
            --c;
        } else if (action == 'R') {
            ++c;
        } else {
            if (picked[r][c]) {
                stream.quitf(_wa, "action %d picks an empty cell (%d, %d)",
                             i + 1, r + 1, c + 1);
            }
            picked[r][c] = true;
            inventory.push_back(board[r][c]);
            if (inventory == target) {
                ++achievedCount;
                inventory.clear();
            }
        }

        if (r < 0 || r >= n || c < 0 || c >= m) {
            stream.quitf(_wa, "action %d moves outside the dungeon", i + 1);
        }
    }

    if (r != n - 1 || c != m - 1) {
        stream.quitf(_wa, "final position is (%d, %d), expected (%d, %d)",
                     r + 1, c + 1, n, m);
    }
    if (!inventory.empty()) {
        stream.quitf(_wa, "character still has %d item(s)",
                     (int)inventory.size());
    }
    if (claimedCount != achievedCount) {
        stream.quitf(_wa, "claimed C is %d but actions achieve %d",
                     claimedCount, achievedCount);
    }

    return {claimedCount, achievedCount, length};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    targetLen = inf.readInt();
    board.resize(n);
    for (int i = 0; i < n; ++i) {
        board[i] = inf.readToken();
    }
    target = inf.readToken();

    Claim jury = readAnswer(ans);
    Claim participant = readAnswer(ouf);

    if (participant.achievedCount < jury.achievedCount) {
        quitf(_wa, "jury achieves %d reinforcement(s), participant achieves %d",
              jury.achievedCount, participant.achievedCount);
    }
    if (participant.achievedCount > jury.achievedCount) {
        quitf(_fail,
              "participant found better answer: jury=%d participant=%d",
              jury.achievedCount, participant.achievedCount);
    }

    quitf(_ok, "answer achieves %d reinforcement(s) with L=%d",
          participant.achievedCount, participant.length);
}
