#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int n;
string currentState, targetState;

struct Answer {
    int cost;
};

Answer readAnswer(InStream& stream) {
    int claimedCost = stream.readInt(0, 90000, "minimum move count");
    stream.readEoln();

    vector<int> delta(n + 1, 0);
    int actualCost = 0;
    int step = 0;
    while (!stream.seekEof()) {
        ++step;
        int index = stream.readInt(1, n, format("rotation[%d].index", step).c_str());
        stream.readSpace();
        int turns = stream.readInt(-9, 9, format("rotation[%d].turns", step).c_str());
        stream.readEoln();

        if (turns == 0) {
            stream.quitf(_wa, "rotation %d has zero turns", step);
        }

        actualCost += abs(turns);
        if (actualCost > 90000) {
            stream.quitf(_wa, "total rotation count exceeds 90000");
        }

        int pos = index - 1;
        if (turns > 0) {
            delta[pos] += turns;
        } else {
            delta[pos] += turns;
            delta[pos + 1] -= turns;
        }
    }

    if (actualCost != claimedCost) {
        stream.quitf(_wa,
                     "claimed move count %d does not match listed rotations total %d",
                     claimedCost,
                     actualCost);
    }

    int carry = 0;
    for (int i = 0; i < n; ++i) {
        carry += delta[i];
        int digit = (currentState[i] - '0' + carry) % 10;
        if (digit < 0) {
            digit += 10;
        }
        int target = targetState[i] - '0';
        if (digit != target) {
            stream.quitf(_wa,
                         "digit %d is %d after rotations, expected %d",
                         i + 1,
                         digit,
                         target);
        }
    }

    return {claimedCost};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    currentState = inf.readToken();
    targetState = inf.readToken();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.cost > jury.cost) {
        quitf(_wa,
              "jury has better answer: jury=%d participant=%d",
              jury.cost,
              participant.cost);
    }
    if (participant.cost < jury.cost) {
        quitf(_fail,
              "participant found a better answer: jury=%d participant=%d",
              jury.cost,
              participant.cost);
    }
    quitf(_ok, "answer=%d", participant.cost);
}
