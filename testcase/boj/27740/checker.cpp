#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int n;
vector<int> initial;

struct Answer {
    int moves;
};

Answer readAnswer(InStream& stream) {
    int moves = stream.readInt(0, n, "M");
    stream.readEoln();

    string ops = stream.readToken(format("[LR]{%d}", moves), "operations");
    stream.readEoln();
    stream.readEof();

    int displacement = 0;
    int minDisplacement = 0;
    int maxDisplacement = 0;
    for (char op : ops) {
        if (op == 'L') {
            --displacement;
        } else {
            ++displacement;
        }
        minDisplacement = min(minDisplacement, displacement);
        maxDisplacement = max(maxDisplacement, displacement);
    }

    for (int position = 1; position <= n; ++position) {
        if (initial[position] == 0) {
            continue;
        }
        bool shiftedOutLeft = minDisplacement <= -position;
        bool shiftedOutRight = maxDisplacement >= n + 1 - position;
        if (!shiftedOutLeft && !shiftedOutRight) {
            stream.quitf(_wa,
                         "1 at position %d remains after the supplied operations",
                         position);
        }
    }

    return {moves};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    initial.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        initial[i] = inf.readInt();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.moves > jury.moves) {
        quitf(_wa,
              "participant uses more operations than jury: participant=%d jury=%d",
              participant.moves,
              jury.moves);
    }
    if (participant.moves < jury.moves) {
        quitf(_fail,
              "participant found fewer valid operations than jury: participant=%d jury=%d",
              participant.moves,
              jury.moves);
    }
    quitf(_ok, "answer uses %d operations", participant.moves);
}
