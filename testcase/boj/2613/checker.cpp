#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int n, m;
vector<int> beads;

struct Answer {
    int value;
};

Answer readAnswer(InStream& stream) {
    int claimed = stream.readInt(1, 30000, "maximum group sum");

    vector<int> groupSizes(m);
    int totalSize = 0;
    int position = 0;
    int actualMaximum = 0;
    for (int i = 0; i < m; ++i) {
        groupSizes[i] = stream.readInt(1, n, format("group size[%d]", i + 1).c_str());
        totalSize += groupSizes[i];
        if (totalSize > n) {
            stream.quitf(_wa, "group sizes exceed n after group %d: total=%d n=%d", i + 1, totalSize, n);
        }

        int groupSum = 0;
        for (int j = 0; j < groupSizes[i]; ++j) {
            groupSum += beads[position++];
        }
        actualMaximum = max(actualMaximum, groupSum);
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after group sizes");
    }

    if (totalSize != n) {
        stream.quitf(_wa, "group sizes sum to %d instead of n=%d", totalSize, n);
    }
    if (claimed != actualMaximum) {
        stream.quitf(_wa,
                     "claimed maximum group sum is %d, but partition maximum is %d",
                     claimed,
                     actualMaximum);
    }

    return {claimed};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    beads.resize(n);
    for (int i = 0; i < n; ++i) {
        beads[i] = inf.readInt();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.value < jury.value) {
        quitf(_fail,
              "participant found a better partition: jury=%d participant=%d",
              jury.value,
              participant.value);
    }
    if (participant.value > jury.value) {
        quitf(_wa,
              "participant maximum group sum is not optimal: jury=%d participant=%d",
              jury.value,
              participant.value);
    }

    quitf(_ok, "maximum group sum %d", participant.value);
}
