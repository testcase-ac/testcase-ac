#include "testlib.h"

#include <vector>

using namespace std;

struct Partition {
    int groups;
    vector<int> label;
};

Partition readPartition(InStream& stream, int graphCount) {
    int groups = stream.readInt(1, graphCount, "number of groups");
    vector<int> label(graphCount + 1, -1);
    vector<int> seen(graphCount + 1, 0);

    for (int group = 0; group < groups; ++group) {
        int size = stream.readInt(1, graphCount, format("group[%d].size", group + 1).c_str());
        for (int pos = 0; pos < size; ++pos) {
            int graph = stream.readInt(1, graphCount, format("group[%d][%d]", group + 1, pos + 1).c_str());
            if (seen[graph]) {
                stream.quitf(_wa, "graph %d appears more than once", graph);
            }
            seen[graph] = 1;
            label[graph] = group;
        }
    }

    for (int graph = 1; graph <= graphCount; ++graph) {
        if (!seen[graph]) {
            stream.quitf(_wa, "graph %d is missing from the partition", graph);
        }
    }

    return {groups, label};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int tests = inf.readInt();
    for (int tc = 1; tc <= tests; ++tc) {
        int graphCount = inf.readInt();
        inf.readInt();
        int initialEdges = inf.readInt();

        for (int i = 0; i < initialEdges; ++i) {
            inf.readInt();
            inf.readInt();
        }
        for (int i = 2; i <= graphCount; ++i) {
            inf.readInt();
            inf.readToken();
            inf.readInt();
            inf.readInt();
        }

        Partition jury = readPartition(ans, graphCount);
        Partition participant = readPartition(ouf, graphCount);

        for (int a = 1; a <= graphCount; ++a) {
            for (int b = a + 1; b <= graphCount; ++b) {
                bool jurySame = jury.label[a] == jury.label[b];
                bool participantSame = participant.label[a] == participant.label[b];
                if (jurySame != participantSame) {
                    quitf(_wa,
                          "test case %d: graphs %d and %d are %s in jury output but %s in participant output",
                          tc,
                          a,
                          b,
                          jurySame ? "same group" : "different groups",
                          participantSame ? "same group" : "different groups");
                }
            }
        }
    }

    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury partition");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant partition");
    }

    quitf(_ok, "all partitions match the jury connectivity-equivalence claims");
}
