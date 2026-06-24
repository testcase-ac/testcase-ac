#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Answer {
    int count;
};

static int n;
static vector<int> switchPos;
static vector<int> bulbPos;

static Answer readAnswer(InStream& stream) {
    int count = stream.readInt(1, n, "count");
    stream.readEoln();

    vector<int> switches(count);
    for (int i = 0; i < count; ++i) {
        switches[i] = stream.readInt(1, n, format("switch[%d]", i + 1).c_str());
        if (i > 0 && switches[i - 1] >= switches[i]) {
            stream.quitf(_wa,
                         "switch numbers must be strictly increasing: switch[%d]=%d, switch[%d]=%d",
                         i, switches[i - 1], i + 1, switches[i]);
        }
    }
    stream.readEoln();
    stream.readEof();

    vector<pair<int, int>> wires;
    wires.reserve(count);
    for (int value : switches) {
        wires.push_back({switchPos[value], bulbPos[value]});
    }
    sort(wires.begin(), wires.end());

    for (int i = 1; i < count; ++i) {
        if (wires[i - 1].second >= wires[i].second) {
            stream.quitf(_wa,
                         "selected wires cross between switch positions %d and %d",
                         wires[i - 1].first, wires[i].first);
        }
    }

    return {count};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    vector<int> switches(n);
    vector<int> bulbs(n);

    switchPos.assign(n + 1, 0);
    bulbPos.assign(n + 1, 0);

    for (int i = 0; i < n; ++i) {
        switches[i] = inf.readInt();
        switchPos[switches[i]] = i + 1;
    }
    for (int i = 0; i < n; ++i) {
        bulbs[i] = inf.readInt();
        bulbPos[bulbs[i]] = i + 1;
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.count < jury.count) {
        quitf(_wa, "jury has better answer: jury=%d participant=%d",
              jury.count, participant.count);
    }
    if (participant.count > jury.count) {
        quitf(_fail, "participant found better answer: jury=%d participant=%d",
              jury.count, participant.count);
    }

    quitf(_ok, "answer count=%d", participant.count);
}
