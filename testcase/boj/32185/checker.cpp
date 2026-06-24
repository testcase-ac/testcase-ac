#include "testlib.h"

#include <vector>

using namespace std;

int n, m;
vector<long long> statSum;
long long jaewonSum;

struct Answer {
    long long value;
    int size;
};

Answer readAnswer(InStream& stream, TResult invalidVerdict) {
    vector<int> team;
    vector<char> used(n + 1, 0);
    long long value = 0;

    while (!stream.seekEof()) {
        int id = stream.readInt(0, n, format("team[%d]", int(team.size()) + 1).c_str());
        if (used[id]) {
            stream.quitf(invalidVerdict, "student %d is listed more than once", id);
        }
        if (id != 0 && statSum[id] > jaewonSum) {
            stream.quitf(invalidVerdict,
                         "student %d has stat sum %lld greater than Jaewon's %lld",
                         id,
                         statSum[id],
                         jaewonSum);
        }

        used[id] = 1;
        team.push_back(id);
        value += statSum[id];

        if (int(team.size()) > m) {
            stream.quitf(invalidVerdict, "team size %d exceeds M=%d", int(team.size()), m);
        }
    }

    if (team.empty()) {
        stream.quitf(invalidVerdict, "team is empty");
    }
    if (!used[0]) {
        stream.quitf(invalidVerdict, "team does not include student 0");
    }

    return {value, int(team.size())};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();

    statSum.assign(n + 1, 0);
    long long v = inf.readLong();
    long long p = inf.readLong();
    long long s = inf.readLong();
    statSum[0] = v + p + s;
    jaewonSum = statSum[0];

    for (int i = 1; i <= n; ++i) {
        v = inf.readLong();
        p = inf.readLong();
        s = inf.readLong();
        statSum[i] = v + p + s;
    }

    Answer jury = readAnswer(ans, _fail);
    Answer participant = readAnswer(ouf, _wa);

    if (participant.value < jury.value) {
        quitf(_wa,
              "jury has better team value: jury=%lld participant=%lld",
              jury.value,
              participant.value);
    }
    if (participant.value > jury.value) {
        quitf(_fail,
              "participant found better team value: jury=%lld participant=%lld",
              jury.value,
              participant.value);
    }

    quitf(_ok, "team value %lld with %d students", participant.value, participant.size);
}
